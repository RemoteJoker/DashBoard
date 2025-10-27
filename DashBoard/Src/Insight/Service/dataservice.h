#ifndef DATASERVICE_H
#define DATASERVICE_H

#include "ServiceImpl/serviceimpl.h"

class DataService final: public ServiceImpl
{
    Q_OBJECT
public:
    DataService();
    ~DataService();

signals:
    void SendCode(int v_service_id,int v_code_type);

public slots:
    void RecvCode(int v_service_id,int v_code_type);

protected:
    void run() final;

private:
    void Core()final;

    void SetServiceId()final;

private:
    int g_service_id;
};

#endif // DATASERVICE_H
