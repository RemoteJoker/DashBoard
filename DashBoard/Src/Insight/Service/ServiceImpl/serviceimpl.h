#ifndef SERVICEIMPL_H
#define SERVICEIMPL_H

#include "Global/runlog.h"
#include "Utils/utils.h"
#include <QThread>

//服务ID
enum ServiceId{
    None = 0,//无服务
    Net,//网络服务
    Data,//数据服务
    Control,//控制服务
    Sql,//数据库服务
    Update,//更新服务
};

//服务类型
enum ServiceType{
    UnDefineError,//未定义错误
    HeartData,//心跳
    HasNewProcessSourceData,//有新Process数据到达
    HasNewCoreDumpSourceData,//有新Dump数据到达
    HasNewVersionSourceData,//有新Version数据到达
    HasNewLogSourceData,//有新Log数据到达
    GetDumpData,//有新数据需要发送
    GetVersionData,//有新数据需要发送
    GetLogData,//有新数据需要发送
    GetUpdate,//请求更新
};

#define m_thread_wait_time 1

class ServiceImpl :public QThread
{
    Q_OBJECT
public:
    explicit ServiceImpl(){}

    virtual ~ServiceImpl() override {}

signals:
    // 参数：发送方服务ID、指令类型
    void SendCode(int v_service_id,int v_code_type);

public slots:
    // 补充：接收其他服务指令的槽函数（子类 ControlService 中需要实现这个槽）
    virtual void RecvCode(int v_service_id,int v_code_type) = 0;

protected:
    virtual void run() override = 0;
    virtual void SetServiceId() = 0;  // 设置当前服务的ID
    virtual void Core() = 0;          // 服务核心逻辑函数

};

#endif // SERVICEIMPL_H
