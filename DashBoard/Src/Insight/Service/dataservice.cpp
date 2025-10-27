#include "dataservice.h"

DataService::DataService()
{
    SetServiceId();
}

DataService::~DataService()
{
    Log(L_INFO,"数据服务结束");
}

void DataService::run(){
    Log(L_INFO,"数据服务运行");
    try {
        //code
        for(;;){
            sleep(m_thread_wait_time);
            Core();
        }
    } catch (...) {
        //
        emit SendCode(Data,UnDefineError);
    }
}

void DataService::RecvCode(int v_service_id,int v_code_type){
}

void DataService::SetServiceId(){
    g_service_id = Data;
}

void DataService::Core(){
    //待定
}
