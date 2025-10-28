#ifndef SQLSERVICE_H
#define SQLSERVICE_H

#include "ServiceImpl/serviceimpl.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>


class SqlService final: public ServiceImpl
{
    Q_OBJECT
public:
    SqlService();
    ~SqlService();
signals:
    void SendCode(int v_service_id,int v_code_type);

public slots:
    void RecvCode(int v_service_id,int v_code_type);

protected:
    void run() final;

private:
    void SetServiceId()final;

    //增加LOG
    bool AddOperateLog(const QString &operation_type, const QString &v_operation, const QDateTime &v_operateTime);

    bool UpdateSoftwareConfig(const QString &newFileVersion);

private:
    int g_service_id;
    QSqlDatabase t_data_base;
    QSqlDatabase t_loader_base;
};

#endif // SQLSERVICE_H
