#ifndef COREDUMPMODEL_H
#define COREDUMPMODEL_H

#include "ModelImpl/modelimpl.h"

typedef struct CoreDumpMsg{
    QString core;
}CoreDumpMsg;

class CoreDumpModel final: public ModelImpl
{
public:
    CoreDumpModel();
public:
    QString Serial(const QStringList v_json_obj)override;
    QStringList AntiSerial(const QString v_str)override;

    QList<QString> GetCoreMsg();

private:
    QList<QString>g_coredump_msg;
};

#endif // COREDUMPMODEL_H
