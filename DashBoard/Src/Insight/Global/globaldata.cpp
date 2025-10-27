#include "globaldata.h"

QQueue<QString> GlobalData::g_source_process_msg;
QQueue<QString> GlobalData::g_source_version_msg;
QQueue<QString> GlobalData::g_source_coredump_msg;
QQueue<QString> GlobalData::g_source_log_info_msg;
QString GlobalData::g_source_coredump_get;
QString GlobalData::g_source_version_get;
QString GlobalData::g_source_log_info_get;
QString GlobalData::g_version_request;
QString GlobalData::g_version_report;
QString GlobalData::g_coredump_request;
QString GlobalData::g_coredump_report;
QString GlobalData::g_loginfo_request;
QString GlobalData::g_loginfo_report;
QString GlobalData::g_process_request;
QString GlobalData::g_process_report;
QString GlobalData::g_heartbeat_dashboard;
QString GlobalData::g_heartbeat_edge;

void GlobalData::SetProcessSub(QString v_str_in,QString v_str_out){
    g_process_report = v_str_in;
    g_process_request = v_str_out;
}

void GlobalData::GetProcessSub(QString &v_str_in,QString &v_str_out){
    v_str_in = g_process_report;
    v_str_out = g_process_request;
}

void GlobalData::SetCoreDumpSub(QString v_str_in,QString v_str_out){
    g_coredump_report = v_str_in;
    g_coredump_request = v_str_out;
}

void GlobalData::GetCoreDumpSub(QString &v_str_in,QString &v_str_out){
    v_str_in = g_coredump_report;
    v_str_out = g_coredump_request;
}

void GlobalData::SetVersionSub(QString v_str_in,QString v_str_out){
    g_version_report = v_str_in;
    g_version_request = v_str_out;
}

void GlobalData::GetVersionSub(QString &v_str_in,QString &v_str_out){
    v_str_in = g_version_report;
    v_str_out = g_version_request;
}

void GlobalData::SetLogInfoSub(QString v_str_in,QString v_str_out){
    g_loginfo_report = v_str_in;
    g_loginfo_request = v_str_out;
}

void GlobalData::GetLogInfoSub(QString &v_str_in,QString &v_str_out){
    v_str_in = g_loginfo_report;
    v_str_out = g_loginfo_request;
}

void GlobalData::SetHeartSub(QString v_str_in,QString v_str_out){
    g_heartbeat_edge = v_str_in;
    g_heartbeat_dashboard = v_str_out;
}

void GlobalData::GetHeartSub(QString &v_str_in,QString &v_str_out){
    v_str_in = g_heartbeat_edge;
    v_str_out = g_heartbeat_dashboard;
}

void GlobalData::SetProcessMsg(QString v_str){
    g_source_process_msg.enqueue(v_str);
}

void GlobalData::SetCoreMsg(QString v_str){
    g_source_coredump_msg.enqueue(v_str);
}

void GlobalData::SetVersionMsg(QString v_str){
    g_source_version_msg.enqueue(v_str);
}

void GlobalData::SetLogInfoMsg(QString v_str){
    g_source_log_info_msg.enqueue(v_str);
}

QString GlobalData::GetProcessMsg(){
    if(g_source_process_msg.size() == 0){
        return "NODATAS";
    }
    return g_source_process_msg.dequeue();
}

int GlobalData::GetProcessMsgNum(){
    return g_source_process_msg.size();
}

QString GlobalData::GetCoreMsg(){
    if(g_source_coredump_msg.size() == 0){
        return "NODATAS";
    }
    return g_source_coredump_msg.dequeue();
}

int GlobalData::GetCoreMsgNum(){
    return g_source_coredump_msg.size();
}

QString GlobalData::GetVersionMsg(){
    if(g_source_version_msg.size() == 0){
        return "NODATAS";
    }
    return g_source_version_msg.dequeue();
}

int GlobalData::GetVersionMsgNum(){
    return g_source_version_msg.size();
}

QString GlobalData::GetLogInfoMsg(){
    if(g_source_log_info_msg.size() == 0){
        return "NODATAS";
    }
    return g_source_log_info_msg.dequeue();
}

int GlobalData::GetLogInfoMsgNum(){
    return g_source_log_info_msg.size();
}

QString GlobalData::GetCoreInfo(){
    return g_source_coredump_get;
}

void GlobalData::SetCoreInfo(QString v_str){
    g_source_coredump_get = v_str;
}

QString GlobalData::GetVersionInfo(){
    return g_source_version_get;
}

void GlobalData::SetVersionInfo(QString v_str){
    g_source_version_get = v_str;
}

QString GlobalData::GetLogInfo(){
    return g_source_log_info_get;
}

void GlobalData::SetLogInfo(QString v_str){
    g_source_log_info_get = v_str;
}
