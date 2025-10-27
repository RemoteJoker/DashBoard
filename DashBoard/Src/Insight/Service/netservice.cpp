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
    mosquitto_lib_init();
    SetServiceId();
}

NetService::~NetService()
{
    Log(L_INFO,"网络服务结束");
    mosquitto_lib_cleanup();
}

void NetService::RecvCode(int v_service_id,int v_code_type){
    if(v_service_id == Control){
        switch(v_code_type){
        case GetDumpData:{
            //接收Core消息
            Log(L_INFO,"网关-发送内核转储请求");
            MQTTSendMessage(m_coredump_request,globalData.GetCoreInfo(),2,true);
        }break;
        case GetVersionData:{
            //接收Version消息
            Log(L_INFO,"网关-发送版本请求");
            MQTTSendMessage(m_version_request,globalData.GetVersionInfo(),2,true);
        }break;
        case GetLogData:{
            //接收Log消息
            Log(L_INFO,"网关-发送日志信息请求");
            MQTTSendMessage(m_loginfo_request,globalData.GetLogInfo(),2,true);
        }break;
        default:break;
        }
    }
}

void NetService::run(){
    Log(L_INFO,"网络服务运行");
    g_mosq = mosquitto_new(nullptr,true,nullptr);
    mosquitto_connect_callback_set(g_mosq, OnConnect);
    mosquitto_subscribe_callback_set(g_mosq, OnSubscribe);
    mosquitto_message_callback_set(g_mosq, OnMessage);
    int rc = mosquitto_connect(g_mosq, "127.0.0.1", 1883, 60);
    Log(L_INFO,"网关注册");
    if(rc != MOSQ_ERR_SUCCESS){
        Log(L_INFO,"网关注册失败");
        mosquitto_destroy(g_mosq);
        return;
    }

    rc = mosquitto_loop_start(g_mosq);
    Log(L_INFO,"网关启动");
    if (rc != MOSQ_ERR_SUCCESS) {
        mosquitto_destroy(g_mosq);
        return;
    }
    Log(L_INFO,"网关运行");
    try {
        //code
        for(;;){
            Log(L_INFO,"网关运行-");
            sleep(m_thread_wait_time);
            Log(L_INFO,"网关运行-");
            Core();
        }
    } catch (...) {
        //
        Log(L_INFO,"心跳3");
        emit SendCode(Net,UnDefineError);
    }
}

void NetService::SetServiceId(){
    g_service_id = Net;
}

void NetService::Core(){
    //发送心跳
    MQTTSendMessage(m_heartbeat_dashboard,"hearts",2,true);//发送心跳请求
    Log(L_INFO,"心跳");
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

void NetService::OnConnect(struct mosquitto *mosq, void *obj, int reason_code)
{
    if(reason_code != 0){
        mosquitto_disconnect(mosq);
        return;
    }
    // 定义要订阅的topic 和对应的 QoS
    TopicQos topics[] = {
        {m_version_report, 2},
        {m_coredump_report, 2},
        {m_loginfo_report, 2},
        {m_process_report, 2},
        {m_heartbeat_edge, 2},
    };

    int topic_count = sizeof(topics) / sizeof(topics[0]);
    bool subscribe_success = false;

    // 循环订阅每个 topic
    for(int i = 0; i < topic_count; i++) {
        int rc = mosquitto_subscribe(mosq, NULL, topics[i].topic, topics[i].qos);
        if(rc != MOSQ_ERR_SUCCESS){
            Log(L_INFO,"MQTT频道"+QString(topics[i].topic).toStdString()+"订阅失败");
            return;
        } else {
            Log(L_INFO,"MQTT频道"+QString(topics[i].topic).toStdString()+"订阅成功");
            subscribe_success = true;
        }
    }

    if(!subscribe_success) {
        Log(L_INFO,"MQTT连接失败");
        mosquitto_disconnect(mosq);
    }
}

/* Callback called when the broker sends a SUBACK in response to a SUBSCRIBE. */
void NetService::OnSubscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos)
{
    bool have_subscription = false;
    for(int i = 0; i < qos_count; i++){
        if(granted_qos[i] <= 2){
            have_subscription = true;
        }
    }

    if(!have_subscription){
        mosquitto_disconnect(mosq);
    } else {
    }
}

void NetService::OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    // 获取 topic 信息
    QString topic = QString::fromUtf8(msg->topic);
    std::string v_payload_str((char*)msg->payload, msg->payloadlen);
    QString v_payload = QString::fromStdString(v_payload_str);
    if(topic == m_process_report) {
        Log(L_INFO,"网关-有进程数据到达"+v_payload.toStdString());
        globalData.SetProcessMsg(v_payload);
    } else if(topic == m_version_report) {
        Log(L_INFO,"网关-有版本数据到达"+v_payload.toStdString());
        globalData.SetVersionMsg(v_payload);
    } else if(topic == m_coredump_report) {
        Log(L_INFO,"网关-有转储数据到达"+v_payload.toStdString());
        globalData.SetCoreMsg(v_payload);
    } else if(topic == m_loginfo_report) {
        Log(L_INFO,"网关-有日志数据到达"+v_payload.toStdString());
        globalData.SetLogInfoMsg(v_payload);
    } else if(topic == m_heartbeat_edge) {
        //心跳线程，暂不存储数据
        heart = true;
    }
}

bool NetService::MQTTSendMessage(const QString& topic, const QString& message, int qos, bool retain)
{
    if (!g_mosq) {
        return false;
    }

    // 直接发送，不需要任何回调
    int rc = mosquitto_publish(
        g_mosq,
        nullptr,                    // message id
        topic.toUtf8().constData(), // topic
        message.length(),           // payload length
        message.toUtf8().constData(), // payload
        qos,                        // QoS
        retain                      // retain
    );

    if (rc != MOSQ_ERR_SUCCESS) {
        return false;
    }
    return true;
}
