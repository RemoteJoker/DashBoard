#ifndef UPDATESERVICE_H
#define UPDATESERVICE_H

#include "ServiceImpl/serviceimpl.h"

class UpdateService : public ServiceImpl
{
    Q_OBJECT
public:
    UpdateService();
    ~UpdateService();

signals:
    void SendCode(int v_service_id,int v_code_type);

public slots:
    void RecvCode(int v_service_id,int v_code_type);

protected:
    void run() final;

private:

    void SetServiceId()final;

private:
    int g_service_id;
};

#endif // UPDATESERVICE_H
