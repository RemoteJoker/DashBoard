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