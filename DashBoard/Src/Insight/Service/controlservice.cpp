#include "controlservice.h"

#include "Service/netservice.h"
#include "Service/sqlservice.h"
#include "Service/updateservice.h"

ContrlService::ContrlService(NetService *v_net_service,SqlService *v_sql_service,UpdateService *v_update_service)
{
    SetServiceId();
    t_net_service = v_net_service;
    t_sql_service = v_sql_service;
    t_update_service = v_update_service;
}

ContrlService::~ContrlService()
{
    Log(L_INFO,"控制服务结束");
}

void ContrlService::run(){
    Log(L_INFO,"控制服务运行");
    connect(this,&ContrlService::SendCode,t_net_service,&NetService::RecvCode);
    connect(t_net_service,&NetService::SendCode,this,&ContrlService::RecvCode);

    connect(this,&ContrlService::SendCode,t_sql_service,&SqlService::RecvCode);
    connect(t_sql_service,&SqlService::SendCode,this,&ContrlService::RecvCode);

    connect(this,&ContrlService::SendCode,t_update_service,&UpdateService::RecvCode);
    connect(t_update_service,&UpdateService::SendCode,this,&ContrlService::RecvCode);

    try {
        //code
        for(;;){
            msleep(m_thread_wait_time);
        }
    } catch (...) {
        //
        emit SendCode(Control,UnDefineError);
    }
}

void ContrlService::RecvCode(int v_service_id,int v_code_type){
    //全处理
    if(v_service_id == None){
        //异常数据:无ID
    }
    if(v_service_id == Net){
        switch(v_code_type){
        default:break;
        }
    }
    if(v_service_id == Sql){
        switch(v_code_type){
        default:break;
        }
    }
    if(v_service_id == Update){
        switch(v_code_type){
        default:break;
        }
    }
}

void ContrlService::SetServiceId(){
    g_service_id = Control;
}

void ContrlService::startRun(){
    emit statusMessageReceived("系统初始化完成");
}

QVariantMap ContrlService::getProcessViewMsg(){
    // 示例数据 - 根据实际数据源替换
    QVariantMap process;
    process["alive"] = false;
    process["pid"] = "xxx";
    process["process_name"] = "agent";
    process["elapsed_time"] = "NULL";
    process["start_time"] = "NULL";
    
    return process;
}

QVariantMap ContrlService::getDumpViewMsg(){
    QVariantMap dumpData;
    QVariantList coresList;
    
    // 示例数据
    QVariantMap core1;
    core1["core"] = "/xdata/log/latest/xxx.core";
    core1["create_time"] = 1759138890;
    coresList.append(core1);
    
    QVariantMap core2;
    core2["core"] = "/xdata/log/latest/yyy.core";
    core2["create_time"] = 1759138890;
    coresList.append(core2);
    
    dumpData["cores"] = coresList;
    return dumpData;
}

QVariantMap ContrlService::getLogViewMsg(){
    QVariantMap logData;
    QVariantList logList;
    
    // 示例数据
    logList << "/xdata/log/0000000000030_2025-09-04.17-09-38.425322020"
            << "/xdata/log/0000000000029_2025-09-04.17-05-22.000000000"
            << "/xdata/log/0000000000035_2025-09-05.12-15-09.488494840";
    
    logData["log_list"] = logList;
    return logData;
}

QVariantMap ContrlService::getVersionViewMsg(){
    QVariantMap versionData;
    
    QString versionInfo = "--------------- Xpilot version --------------- \n"
                         "Version: v0.1.Q-IDK1.4.0\n"
                         "Built Time: 20250923220222\n"
                         "Vehicle: e29\n"
                         "Vehicle Full Name: e29\n"
                         "EEA Vesion: EEA_3_6\n"
                         "Xpilot SDK Version: 1.3.0-patch121\n"
                         "XP5 PDK Version: 1.3.0.121\n"
                         "Current ChipMode: SoC_VLMU\n"
                         "MCU BSW Verison: 00000000000000003\n"
                         "Vin: Privilege: ENG_DEV\n"
                         "------ VLMU /xdata/xai/model/version.txt ------\n"
                         "Version: \"V0.0.D\"\n"
                         "Time: \"20250917114222\"\n"
                         "----------------- PDK version ----------------- \n"
                         "Version: 1.3.0.121\n"
                         "Branch: release_v1.3.0\n"
                         "Built Time: 2025-09-13-20:26:25 CST\n"
                         "Build Type: Release\n"
                         "----------------------------------------------- ";
    
    versionData["version_info"] = versionInfo;
    return versionData;
}

void ContrlService::executeDumpCommand()
{
    // 转储指令的具体实现
    emit statusMessageReceived("执行转储指令");
    // 调用实际的转储逻辑，例如生成核心转储文件等
    // 可以在这里触发转储操作
}

void ContrlService::executeLogCommand()
{
    // 日志指令的具体实现
    emit statusMessageReceived("执行日志指令");
    // 调用实际的日志逻辑，例如导出日志、清理日志等
    // 可以在这里处理日志相关操作
}

void ContrlService::executeVersionCommand()
{
    // 版本指令的具体实现
    emit statusMessageReceived("执行版本指令");
    // 调用实际的版本逻辑，例如检查更新、版本验证等
    // 可以在这里处理版本相关操作
}