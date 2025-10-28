#include "sqlservice.h"

SqlService::SqlService()
{
    SetServiceId();

    /*启动器配置数据库路径解析*/
    QDir v_current_dir(Utils::GetRunPath());
    v_current_dir.cdUp();
    v_current_dir.cdUp();
    QString v_loader_path = v_current_dir.absolutePath()+"/bin/launch.db";

    t_data_base = QSqlDatabase::addDatabase("QSQLITE", "main_user_conn");
    t_data_base.setDatabaseName(Utils::GetRunPath()+"/configure/data/vlmu.db");
    // 尝试打开数据库
    if (!t_data_base.open()) {
        Log(L_ERROR,"主数据库打开失败");
    } else {
        //创建操作记录表
        QSqlQuery v_operate_sql(t_data_base);
        //操作表(操作内容；操作时间)
        QString v_operate_log = R"(
            CREATE TABLE IF NOT EXISTS operatelog (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                operation_type TEXT NOT NULL,
                operation_content TEXT NOT NULL,
                operation_time DATETIME NOT NULL
            )
        )";
        v_operate_sql.exec(v_operate_log);
    }

    t_loader_base = QSqlDatabase::addDatabase("QSQLITE", "main_loader_conn");
    t_loader_base.setDatabaseName(v_loader_path);
    // 尝试打开数据库
    if (!t_loader_base.open()) {
        Log(L_ERROR,"启动器数据库打开失败");
    } else {
        //创建操作记录表
        QSqlQuery v_operate_sql(t_loader_base);
        //操作表(操作内容；操作时间)
        QString v_operate_log = R"(
            CREATE TABLE IF NOT EXISTS software_config (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                newfile_version TEXT NOT NULL, -- 新版本号
                oldfile_version TEXT NOT NULL  -- 旧版本号
            )
        )";
        v_operate_sql.exec(v_operate_log);
    }

}

SqlService::~SqlService()
{
    Log(L_INFO,"数据库服务结束");
    t_data_base.close();
}

void SqlService::run(){
    Log(L_INFO,"数据库服务运行");
    try {
        //code
        for(;;){
            msleep(m_thread_wait_time);
        }
    } catch (...) {
        //
        emit SendCode(Sql,UnDefineError);
    }
}

void SqlService::RecvCode(int v_service_id,int v_code_type){
    //全处理
    if(v_service_id == g_service_id){
        //处理
    }
}

void SqlService::SetServiceId(){
    g_service_id = Sql;
}

bool SqlService::AddOperateLog(const QString &operation_type, const QString &v_operation, const QDateTime &v_operateTime){
    QSqlQuery v_query(t_data_base);
    v_query.prepare("INSERT INTO operatelog (operation_type, operation_content, operate_time) VALUES (?, ?, ?)");
    v_query.addBindValue(operation_type);
    v_query.addBindValue(v_operation);
    v_query.addBindValue(v_operateTime.toString("yyyy-MM-dd hh:mm:ss"));

    v_query.exec();
    return true;
}

bool SqlService::UpdateSoftwareConfig(const QString &newVersion) {
    // 1. 检查数据库是否打开
    if (!t_loader_base.isOpen()) {
        Log(L_ERROR, "数据库未连接，无法执行更新");
        return false;
    }

    // 2. 开始事务
    if (!t_loader_base.transaction()) {
        Log(L_ERROR, "开启事务失败");
        return false;
    }

    QSqlQuery query(t_loader_base);
    bool success = false;
    QString oldNewVersion = "";  // 存储当前数据库中的new_version（将作为本次的old_version）

    try {
        // 3. 第一步：查询当前最新版本（new_version），作为本次更新的旧版本
        if (query.exec("SELECT new_version FROM software_config WHERE id = 1")) {
            if (query.next()) {
                oldNewVersion = query.value("new_version").toString();
                Log(L_INFO, QString("读取到历史最新版本: %1，将作为本次旧版本").arg(oldNewVersion).toUtf8().constData());
            } else {
                // 首次更新：无历史版本，old_version留空
                Log(L_INFO, "数据库无历史版本，本次为首次更新");
            }
        } else {
            throw QString("查询历史版本失败: %1").arg(query.lastError().text());
        }

        // 4. 第二步：执行插入/更新（仅处理版本号）
        if (query.exec("SELECT id FROM software_config WHERE id = 1")) {
            if (query.next()) {
                // 已有记录：更新（old_version=原new_version，new_version=传入的新版本）
                query.prepare(R"(
                    UPDATE software_config
                    SET oldfile_version = :oldVer,  -- 原最新版本 → 旧版本
                        newfile_version = :newVer   -- 传入的新版本 → 最新版本
                    WHERE id = 1
                )");
            } else {
                // 无记录：插入（首次初始化）
                query.prepare(R"(
                    INSERT INTO software_config
                    (oldfile_version, new_version)
                    VALUES (:oldVer, :newVer)
                )");
            }

            // 5. 绑定参数（仅版本号）
            query.bindValue(":oldVer", oldNewVersion);  // 原最新版本 → 旧版本
            query.bindValue(":newVer", newVersion);     // 传入的新版本 → 最新版本

            // 6. 执行SQL
            if (!query.exec()) {
                throw QString("执行版本更新失败: %1").arg(query.lastError().text());
            }
        } else {
            throw QString("查询记录存在性失败: %1").arg(query.lastError().text());
        }

        // 7. 提交事务
        if (!t_loader_base.commit()) {
            throw QString("提交事务失败: %1").arg(t_loader_base.lastError().text());
        }

        success = true;
        Log(L_INFO, QString("版本更新成功：旧版本=%1，新版本=%2")
            .arg(oldNewVersion).arg(newVersion).toUtf8().constData());
    } catch (const QString &errorMsg) {
        // 8. 错误回滚
        t_loader_base.rollback();
        Log(L_ERROR, QString("更新事务失败: %1").arg(errorMsg).toUtf8().constData());
        success = false;
    }

    return success;
}
