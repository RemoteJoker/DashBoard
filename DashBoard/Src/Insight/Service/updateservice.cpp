#include "updateservice.h"
#include <QLibrary>

UpdateService::UpdateService()
{
    SetServiceId();
    //加载更新库
    QLibrary v_upload_library(Utils::GetRunPath()+"/bin/Upload.dll");
    if (!v_upload_library.load()) {
        Log(L_ERROR,"更新库加载失败");
    }
}

UpdateService::~UpdateService()
{
    Log(L_INFO,"更新服务结束");
}

void UpdateService::run(){
    Log(L_INFO,"更新服务运行");
    try {
        //code
        for(;;){
            sleep(m_thread_wait_time);
            Core();
        }
    } catch (...) {
        //
        emit SendCode(Update,UnDefineError);
    }
}

void UpdateService::RecvCode(int v_service_id,int v_code_type){
    if(v_service_id == Control){
        switch(v_code_type){
        case GetUpdate:{
            Log(L_INFO,"网关-启动更新");
            //启动第三方模块获取更新
        }break;
        default:break;
        }
    }
}

void UpdateService::SetServiceId(){
    g_service_id = Update;
}

void UpdateService::Core(){
    //待定
}
