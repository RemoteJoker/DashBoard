#ifndef NETSERVICE_H
#define NETSERVICE_H

#include "ServiceImpl/serviceimpl.h"

/*use Mqtt*/
#include <mosquito/mosquitto.h>

typedef struct TopicQos {
    const char* topic;
    int qos;
}TopicQos;

class NetService final: public ServiceImpl
{
    Q_OBJECT
public:
    NetService();
    ~NetService();

signals:
    void SendCode(int v_service_id,int v_code_type);

public slots:
    void RecvCode(int v_service_id,int v_code_type);

protected:
    void run() final;

private:
    static void OnConnect(struct mosquitto *mosq, void *obj, int reason_code);
    static void OnSubscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos);
    static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
    bool MQTTSendMessage(const QString& topic, const QString& message, int qos = 1, bool retain = false);

    void Core()final;

    void SetServiceId()final;

private:
    int g_service_id;
    struct mosquitto *g_mosq;
    static bool heart;//心跳包独特逻辑
};

#endif // NETSERVICE_H
