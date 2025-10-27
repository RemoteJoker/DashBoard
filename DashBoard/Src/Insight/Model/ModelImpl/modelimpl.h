#ifndef MODELIMPL_H
#define MODELIMPL_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMap>

class ModelImpl
{
public:
    explicit ModelImpl(){}
    virtual ~ModelImpl() {}

    virtual QString Serial(const QStringList v_json_obj) = 0;//序列化
    virtual QStringList AntiSerial(const QString v_str) = 0;//反序列化
};

#endif // MODELIMPL_H
