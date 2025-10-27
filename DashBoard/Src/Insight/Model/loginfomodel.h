#ifndef LOGINFOMODEL_H
#define LOGINFOMODEL_H

#include "ModelImpl/modelimpl.h"

class LogInfoModel final: public ModelImpl
{
public:
    LogInfoModel();
public:
    QString Serial(const QStringList v_json_obj)override;
    QStringList AntiSerial(const QString v_str)override;

    QList<QString> GetLogInfoMsg();

private:
    QList<QString>g_log_info_msg;
};

#endif // LOGINFOMODEL_H
