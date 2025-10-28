#ifndef NETSERVICE_H
#define NETSERVICE_H

#include "ServiceImpl/serviceimpl.h"

/*use Mqtt*/
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttTopicName>
#include <QtMqtt/QMqttTopicFilter>

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

private slots:
    void Connected();
    void Disconnected();
    void MessageReceived(const QByteArray &message, const QMqttTopicName &topic);

public slots: 
    void RecvCode(int v_service_id,int v_code_type);

protected:
    void run() final;

private:
    void SetServiceId()final;

    void SubScribe(const QString &topic);

    void Publish(const QString &topic, const QString &message);


private:
    int g_service_id;
    QMqttClient *t_client;
    static bool heart;//心跳包独特逻辑
};

#endif // NETSERVICE_H
