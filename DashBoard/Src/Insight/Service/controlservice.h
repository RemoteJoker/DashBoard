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
    ContrlService(NetService *,SqlService *,UpdateService*);
    ~ContrlService();

signals:
    void SendCode(int v_service_id,int v_code_type);//接收指令码从更新线程

public slots:
    void RecvCode(int v_service_id,int v_code_type);

protected:
    void run() final;

private:
    void SetServiceId()final;


private:
    int g_service_id;//服务号/必须
    DataService *t_data_service;
    NetService *t_net_service;
    SqlService *t_sql_service;
    UpdateService *t_update_service;
};

#endif // CONTROLSERVICE_H