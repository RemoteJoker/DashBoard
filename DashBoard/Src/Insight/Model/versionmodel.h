#ifndef VERSIONMODEL_H
#define VERSIONMODEL_H

#include "ModelImpl/modelimpl.h"

typedef struct VersionMsg{
}VersionMsg;

class VersionModel final: public ModelImpl
{
public:
    VersionModel();

public:
    QString Serial(const QStringList v_json_obj)override;
    QStringList AntiSerial(const QString v_str)override;

    QList<QString> GetVersionMsg();

private:
    QList<QString>g_version_msg;
};

#endif // VERSIONMODEL_H
