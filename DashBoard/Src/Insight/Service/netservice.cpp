#include "netservice.h"
#include "Global/globaldata.h"

//mosquitto_sub -h 127.0.0.1 -t m_version_request -v
//mosquitto_sub -h 127.0.0.1 -t m_coredump_request -v
//mosquitto_sub -h 127.0.0.1 -t m_loginfo_request -v
//mosquitto_pub -h 127.0.0.1 -t m_version_report -m '{"cmd_type":"vlmu_version","command_id": 1234,"response_id": 1234,"ret": "xxxx","version_info": "--------------- Xpilot version --------------- \nVersion: v0.1.Q-IDK1.4.0\nBuilt Time: 20250923220222\nVehicle: e29\nVehicle Full Name: e29\nEEA Vesion: EEA_3_6\nXpilot SDK Version: 1.3.0-patch121\nXP5 PDK Version: 1.3.0.121\nCurrent ChipMode: SoC_VLMU\nMCU BSW Verison: 00000000000000003\nVin: Privilege: ENG_DEV\n------ VLMU /xdata/xai/model/version.txt ------\nVersion: \"V0.0.D\"\nTime: \"20250917114222\"\n----------------- PDK version ----------------- \nVersion: 1.3.0.121\nBranch: release_v1.3.0\nBuilt Time: 2025-09-13-20:26:25 CST\nBuild Type: Release\n----------------------------------------------- ","timestamp": 1759138890}'
//mosquitto_pub -h 127.0.0.1 -t m_coredump_report -m '{"cmd_type":"vlmu_coredump","command_id": 1234,"response_id": 1234,"ret": "xxxx","cores": ["/xdata/log/latest/xxx.core", "/xdata/log/latest/yyy.core"],"timestamp": 1759138890}'
//mosquitto_pub -h 127.0.0.1 -t m_loginfo_report -m '{"cmd_type": "vlmu_loginfo","command_id": 1234,"response_id": 1234,"ret": "xxxx","log_list": ["/xdata/log/0000000000030_2025-09-04.17-09-38.425322020","/xdata/log/0000000000029_2025-09-04.17-05-22.000000000","/xdata/log/0000000000035_2025-09-05.12-15-09.488494840","/xdata/log/0000000000031_2025-09-04.17-12-17.000000000","/xdata/log/0000000000032_2025-09-04.17-19-11.000000000","/xdata/log/0000000000033_2025-09-05.08-51-13.000000000","/xdata/log/0000000000034_2025-09-05.11-57-23.000000000"],"timestamp": 1759138890}'

GlobalData& globalData = GlobalData::getInstance();
bool NetService::heart = false;

NetService::NetService()
{
    t_client = new QMqttClient;
    t_client->setHostname("127.0.0.1");
    t_client->setPort(1883);
    t_client->connectToHost();
    SetServiceId();
}

NetService::~NetService()
{
    Log(L_INFO,"网络服务结束");
}

void NetService::RecvCode(int v_service_id,int v_code_type){
    if(v_service_id == g_service_id){
        //处理信息
        switch(v_code_type){
        case GetDumpData:{
            //接收Core消息
            Log(L_INFO,"网关-发送内核转储请求");
            Publish(m_coredump_request,globalData.GetCoreInfo());
        }break;
        case GetVersionData:{
            //接收Version消息
            Log(L_INFO,"网关-发送版本请求");
            Publish(m_version_request,globalData.GetVersionInfo());
        }break;
        case GetLogData:{
            //接收Log消息
            Log(L_INFO,"网关-发送日志信息请求");
            Publish(m_loginfo_request,globalData.GetLogInfo());
        }break;
        default:break;
        }
    }
}

void NetService::run(){
    Log(L_INFO,"网络服务运行");
    connect(t_client, &QMqttClient::connected, this, &NetService::Connected);
    connect(t_client, &QMqttClient::disconnected, this, &NetService::Disconnected);
    connect(t_client, &QMqttClient::messageReceived, this, &NetService::MessageReceived);
    try {
        //code
        for(;;){
            Log(L_INFO,"网关运行-");
            msleep(m_thread_wait_time);
            Publish(m_heartbeat_dashboard,"hearts");
            if(globalData.GetProcessMsgNum() != 0){
                Log(L_INFO,"网关-处理进程信息");
                emit SendCode(Net,HasNewProcessSourceData);
            }
            if(globalData.GetCoreMsgNum() != 0){
                Log(L_INFO,"网关-处理进程信息");
                emit SendCode(Net,HasNewCoreDumpSourceData);
            }
            if(globalData.GetVersionMsgNum() != 0){
                Log(L_INFO,"网关-处理进程信息");
                emit SendCode(Net,HasNewVersionSourceData);
            }
            if(globalData.GetLogInfoMsgNum() != 0){
                Log(L_INFO,"网关-处理进程信息");
                emit SendCode(Net,HasNewLogSourceData);
            }
            if(heart){
                Log(L_INFO,"网关-处理心跳信息");
                emit SendCode(Net,HeartData);
                heart = false;
            }
        }
    } catch (...) {
        //
        Log(L_INFO,"心跳3");
        emit SendCode(Net,UnDefineError);
    }
}

void NetService::Connected(){}

void NetService::Disconnected(){}

void NetService::MessageReceived(const QByteArray &message, const QMqttTopicName &topic){
    //接收到消息
    if(topic.name() == m_process_report) {
        Log(L_INFO,"网关-有进程数据到达"+message.toStdString());
        globalData.SetProcessMsg(message);
    } else if(topic.name() == m_version_report) {
        Log(L_INFO,"网关-有版本数据到达"+message.toStdString());
        globalData.SetVersionMsg(message);
    } else if(topic.name() == m_coredump_report) {
        Log(L_INFO,"网关-有转储数据到达"+message.toStdString());
        globalData.SetCoreMsg(message);
    } else if(topic.name() == m_loginfo_report) {
        Log(L_INFO,"网关-有日志数据到达"+message.toStdString());
        globalData.SetLogInfoMsg(message);
    } else if(topic.name() == m_heartbeat_edge) {
        //心跳线程，暂不存储数据
        heart = true;
    }
}

void NetService::SetServiceId(){
    g_service_id = Net;
}

void NetService::SubScribe(const QString &topic){
    t_client->subscribe(topic,2);
}

void NetService::Publish(const QString &topic, const QString &message){
    t_client->publish(topic, message.toUtf8(),2);
}