#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include "ModelImpl/modelimpl.h"

//进程模型
typedef struct ProcessMsg{
    QString start_time;//开始时间
    QString elapsed_time;//持续时间
    QString process_id;//进程ID
    bool alive;//是否存活
}ProcessMsg;

class ProcessModel final: ModelImpl
{
public:
    ProcessModel();

public:
    QString Serial(const QStringList v_json_obj)override;
    QStringList AntiSerial(const QString v_str)override;

    QMap<QString,ProcessMsg> GetProcessMsg();

private:
    QMap<QString,ProcessMsg>g_process_msg;
};

#endif // PROCESSMODEL_H
