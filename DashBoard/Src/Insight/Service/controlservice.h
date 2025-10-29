#ifndef CONTROLSERVICE_H
#define CONTROLSERVICE_H

#include "ServiceImpl/serviceimpl.h"

class DataService;
class NetService;
class SqlService;
class UpdateService;

class ControlService final: public ServiceImpl
{
    Q_OBJECT

public:
    ControlService(NetService *,SqlService *,UpdateService*);
    ~ControlService();

signals:
    void SendCode(int v_service_id,int v_code_type);//接收指令码从更新线程

    // 状态栏消息信号
    Q_INVOKABLE void statusMessageReceived(QString v_message);//发送给状态栏的信号

    // 托盘消息信号  
    Q_INVOKABLE void trayMessageReceived(QString v_message);//发送给托盘的信号

public slots:
    Q_INVOKABLE void startRun(); // 发送初始化包

    Q_INVOKABLE QVariantMap getProcessViewMsg(); // 获取进程数据

    Q_INVOKABLE QVariantMap getDumpViewMsg(); // 获取转储数据

    Q_INVOKABLE QVariantMap getLogViewMsg(); // 获取日志数据

    Q_INVOKABLE QVariantMap getVersionViewMsg(); // 获取版本数据

    Q_INVOKABLE void executeDumpCommand();

    Q_INVOKABLE void executeLogCommand();
    
    Q_INVOKABLE void executeVersionCommand();   // 版本指令

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