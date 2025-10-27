#include "controlservice.h"

#include "Service/dataservice.h"
#include "Service/netservice.h"
#include "Service/sqlservice.h"
#include "Service/updateservice.h"

ContrlService::ContrlService(DataService *v_data_service,NetService *v_net_service,SqlService *v_sql_service,UpdateService *v_update_service)
{
    SetServiceId();
    t_data_service = v_data_service;
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

    connect(this,&ContrlService::SendCodeToData,t_data_service,&DataService::RecvCode);
    connect(t_data_service,&DataService::SendCode,this,&ContrlService::RecCodeFromData);

    connect(this,&ContrlService::SendCodeToNet,t_net_service,&NetService::RecvCode);
    connect(t_net_service,&NetService::SendCode,this,&ContrlService::RecCodeFromNet);

    connect(this,&ContrlService::SendCodeToSql,t_sql_service,&SqlService::RecvCode);
    connect(t_sql_service,&SqlService::SendCode,this,&ContrlService::RecCodeFromSql);

    connect(this,&ContrlService::SendCodeToUpdate,t_update_service,&UpdateService::RecvCode);
    connect(t_update_service,&UpdateService::SendCode,this,&ContrlService::RecCodeFromUpdate);

    try {
        //code
        for(;;){
            sleep(m_thread_wait_time);
            Core();
        }
    } catch (...) {
        //
        emit SendCodeToWindow(Control,UnDefineError);
    }
}

void ContrlService::RecvCode(int v_service_id,int v_code_type){
    //实现基类，无作用
}

void ContrlService::RecCodeFromWindow(int v_service_id,int v_code_type){
    if(v_service_id == Control){
        switch(v_code_type){
        case GetDumpData:{
            emit SendCodeToNet(Control,GetDumpData);
        }break;
        case GetVersionData:{
            emit SendCodeToNet(Control,GetVersionData);
        }break;
        case GetLogData:{
            emit SendCodeToNet(Control,GetLogData);
        }break;
        case GetUpdate:{
            emit SendCodeToUpdate(Control,GetUpdate);
        }break;
        default:break;
        }
    }
}

void ContrlService::RecCodeFromData(int v_service_id,int v_code_type){
    if(v_service_id == Data){
        switch(v_code_type){
        case UnDefineError:{
            emit SendCodeToWindow(Data,UnDefineError);
        }break;
        case HasNewProcessSourceData:{
            //刷新进程信息
            emit SendCodeToWindow(Control,HasNewProcessSourceData);
        }break;
        case HasNewCoreDumpSourceData:{
            emit SendCodeToData(Control,HasNewCoreDumpSourceData);
        }break;
        case HasNewVersionSourceData:{
            emit SendCodeToData(Control,HasNewVersionSourceData);
        }break;
        case HasNewLogSourceData:{
            emit SendCodeToData(Control,HasNewLogSourceData);
        }break;
        default:break;
        }
    }
}

void ContrlService::RecCodeFromNet(int v_service_id,int v_code_type){
    if(v_service_id == Net){
        switch(v_code_type){
        case UnDefineError:{
            emit SendCodeToWindow(Net,UnDefineError);
        }break;
        case HasNewProcessSourceData:{
            emit SendCodeToData(Data,HasNewProcessSourceData);
        }break;
        case HasNewCoreDumpSourceData:{
            emit SendCodeToData(Data,HasNewCoreDumpSourceData);
        }break;
        case HasNewVersionSourceData:{
            emit SendCodeToData(Data,HasNewVersionSourceData);
        }break;
        case HasNewLogSourceData:{
            emit SendCodeToData(Data,HasNewLogSourceData);
        }break;
        case HeartData:{
            emit SendCodeToWindow(Net,HeartData);
        }break;
        default:break;
        }
    }
}

void ContrlService::RecCodeFromSql(int v_service_id,int v_code_type){
    if(v_service_id == Sql){
        switch(v_code_type){
        case UnDefineError:{
            emit SendCodeToWindow(Sql,UnDefineError);
        }break;
//        case HasNewProcessSourceData:{
//            emit SendCodeToData(Data,HasNewProcessSourceData);
//        }break;
        default:break;
        }
    }
}

void ContrlService::RecCodeFromUpdate(int v_service_id,int v_code_type){
    if(v_service_id == Update){
        switch(v_code_type){
        case UnDefineError:{
            emit SendCodeToWindow(Update,UnDefineError);
        }break;
        default:break;
        }
    }
}

void ContrlService::SetServiceId(){
    g_service_id = Control;
}

void ContrlService::Core(){
    //待定
}
