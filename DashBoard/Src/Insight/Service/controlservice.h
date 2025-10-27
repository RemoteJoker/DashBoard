#ifndef CONTROLSERVICE_H
#define CONTROLSERVICE_H

#include "ServiceImpl/serviceimpl.h"

class DataService;
class NetService;
class SqlService;
class UpdateService;

class ContrlService final: public ServiceImpl
{
    Q_OBJECT
public:
    ContrlService(DataService *,NetService *,SqlService *,UpdateService*);
    ~ContrlService();

signals:
    void SendCodeToWindow(int v_service_id,int v_code_type);//发送指令码到主界面
    void SendCodeToData(int v_service_id,int v_code_type);//发送指令码到数据线程
    void SendCodeToNet(int v_service_id,int v_code_type);//发送指令码到网络线程
    void SendCodeToSql(int v_service_id,int v_code_type);//发送指令码到数据库线程
    void SendCodeToUpdate(int v_service_id,int v_code_type);//接收指令码从更新线程

public slots:
    void RecvCode(int v_service_id,int v_code_type);
    void RecCodeFromWindow(int v_service_id,int v_code_type);//接收指令码从主界面
    void RecCodeFromData(int v_service_id,int v_code_type);//接收指令码从数据线程
    void RecCodeFromNet(int v_service_id,int v_code_type);//接收指令码从网络线程
    void RecCodeFromSql(int v_service_id,int v_code_type);//接收指令码从数据库线程
    void RecCodeFromUpdate(int v_service_id,int v_code_type);//接收指令码从更新线程

public slots:

protected:
    void run() final;

private:
    void Core()final;

    void SetServiceId()final;

private:
    int g_service_id;//服务号/必须
    DataService *t_data_service;
    NetService *t_net_service;
    SqlService *t_sql_service;
    UpdateService *t_update_service;
};

#endif // CONTROLSERVICE_H
