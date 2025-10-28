#include "utils.h"

Utils::Utils()
{

}

bool Utils::InitApp(){
    //初始化应用程序-读取配置文件
    if(1){
        SetRunPath();
        QString g_exe_path = GetRunPath();
        //读取全局配置文件
        QSettings v_app_settings(g_exe_path+"/configure/app.ini", QSettings::IniFormat);
        GlobalSet::SetMainWindow(v_app_settings.value("mainwindow/m_mainwindow_name").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_version").toString()
                                 ,g_exe_path+v_app_settings.value("mainwindow/m_mainwindow_style").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_width").toUInt()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_height").toUInt()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu0_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu1_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu1_cmdview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu1_setview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_processview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_dumpview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_versionview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu2_logview").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu3_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu4_title").toString()
                                 ,v_app_settings.value("mainwindow/m_mainwindow_menu4_aboutview").toString()
                                 );
        GlobalSet::SetSetWindow(v_app_settings.value("setwindow/m_setwindow_name").toString()
                                ,g_exe_path+v_app_settings.value("setwindow/m_setwindow_style").toString()
                                );
        GlobalSet::SetCmdWindow(v_app_settings.value("cmdwindow/m_cmdwindow_name").toString()
                                ,g_exe_path+v_app_settings.value("cmdwindow/m_cmdwindow_style").toString()
                                ,v_app_settings.value("cmdwindow/m_cmdwindow_button_1").toString()
                                ,v_app_settings.value("cmdwindow/m_cmdwindow_button_2").toString()
                                ,v_app_settings.value("cmdwindow/m_cmdwindow_button_3").toString()
                                );
        GlobalSet::SetProcessWindow(v_app_settings.value("processwindow/m_processwindow_name").toString()
                                    ,g_exe_path+v_app_settings.value("processwindow/m_processwindow_style").toString()
                                    ,v_app_settings.value("processwindow/m_processwindow_num").toUInt()
                                    ,v_app_settings.value("processwindow/m_processwindow_list").toString().split('@')
                                    ,v_app_settings.value("processwindow/m_processwindow_flush").toString()
                                    ,v_app_settings.value("processwindow/m_processwindow_hide").toString()
                                    );
        GlobalSet::SetDumpWindow(v_app_settings.value("dumpwindow/m_dumpwindow_name").toString()
                                 ,g_exe_path+v_app_settings.value("dumpwindow/m_dumpwindow_style").toString()
                                 ,v_app_settings.value("dumpwindow/m_dumpwindow_flush").toString()
                                 ,v_app_settings.value("dumpwindow/m_dumpwindow_hide").toString()
                                 );
        GlobalSet::SetVersionWindow(v_app_settings.value("versionwindow/m_versionwindow_name").toString()
                                    ,g_exe_path+v_app_settings.value("versionwindow/m_versionwindow_style").toString()
                                    ,v_app_settings.value("versionwindow/m_versionwindow_flush").toString()
                                    ,v_app_settings.value("versionwindow/m_versionwindow_hide").toString()
                                    );
        GlobalSet::SetLogWindow(v_app_settings.value("logwindow/m_logwindow_name").toString()
                                ,g_exe_path+v_app_settings.value("logwindow/m_logwindow_style").toString()
                                ,v_app_settings.value("logwindow/m_logwindow_flush").toString()
                                ,v_app_settings.value("logwindow/m_logwindow_hide").toString()
                                );
        GlobalSet::SetAboutWindow(v_app_settings.value("aboutwindow/m_aboutwindow_name").toString()
                                  ,g_exe_path+v_app_settings.value("aboutwindow/m_aboutwindow_style").toString()
                                  );
        //读取MQTT通信相关配置文件
        QSettings v_mosqsub_settings(g_exe_path+"/configure/app/mosqsub.ini", QSettings::IniFormat);
        GlobalData::SetProcessSub(v_mosqsub_settings.value("process/m_process_report").toString()
                                  ,v_mosqsub_settings.value("process/m_process_request").toString()
                                  );
        GlobalData::SetCoreDumpSub(v_mosqsub_settings.value("coredump/m_coredump_report").toString()
                                  ,v_mosqsub_settings.value("coredump/m_coredump_request").toString()
                                  );
        GlobalData::SetVersionSub(v_mosqsub_settings.value("version/m_version_report").toString()
                                  ,v_mosqsub_settings.value("version/m_version_request").toString()
                                  );
        GlobalData::SetLogInfoSub(v_mosqsub_settings.value("loginfo/m_loginfo_report").toString()
                                  ,v_mosqsub_settings.value("loginfo/m_loginfo_request").toString()
                                  );
        GlobalData::SetHeartSub(v_mosqsub_settings.value("heart/m_heartbeat_edge").toString()
                                  ,v_mosqsub_settings.value("heart/m_heartbeat_dashboard").toString()
                                  );

        return true;
    }else{
        return false;
    }
}

qint64 Utils::GetTimeStampS(){
    return QDateTime::currentDateTime().toSecsSinceEpoch();
}

qint64 Utils::GetTimeStampMS(){
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

QString Utils::GetRunPath(){
#ifdef _WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\VLMU", QSettings::NativeFormat);
    // 写入各种类型的数据
    return settings.value("RunPath").toString();
#elif
    return QString();
#endif
}

void Utils::SetRunPath(){
    QString v_str = QCoreApplication::applicationDirPath();
#ifdef _WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\VLMU", QSettings::NativeFormat);
    settings.setValue("RunPath", v_str);
    settings.sync();
#elif

#endif
}

QString Utils::DeCryptData(){
    return QString();
}

QString Utils::EnCryptData(){
    return QString();
}

bool Utils::CheckDirExist(QString str){
    //
    QDir dir(str);
    if (!dir.exists()) {
        return false;
    }
    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    return !list.isEmpty();
}

bool Utils::CheckFileExist(QString str){
    QDir dir(str);
    if (!dir.exists()) {
        return false;
    }

    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    return !list.isEmpty();
}

bool Utils::CheckMySqlSrv(){
#ifdef __linux__
    // Linux系统：检查mysqld进程
    QProcess process;
    process.start("pgrep", QStringList() << "mysqld");
    process.waitForFinished();
    return (process.exitCode() == 0);

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    // Windows系统：检查MySQL服务状态
    QProcess process;
    process.start("sc", QStringList() << "query" << "MySQL");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    return output.contains("RUNNING");

#else
    return false;
#endif
}

bool Utils::CheckFileIntegrity(){
    return false;
}
