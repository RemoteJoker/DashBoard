#ifndef SERVICEIMPL_H
#define SERVICEIMPL_H

#include "Global/GlobalLog.h"
#include "Utils/utils.h"
#include <QThread>

//服务ID
enum ServiceId{
    None = 0,//无服务
    Net,//网络服务
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
    GetDumpData,//请求DUMP数据
    GetVersionData,//请求VERSION数据
    GetLogData,//请求LOG数据
    GetUpdate,//请求更新
};

#define m_thread_wait_time 200

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
    virtual void RecvCode(int v_service_id,int v_code_type) = 0;

protected:
    virtual void run() override = 0;
    virtual void SetServiceId() = 0;  // 设置当前服务的ID

};

#endif // SERVICEIMPL_H
