#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Service/controlservice.h"
#include "Service/sqlservice.h"
#include "Service/netservice.h"
#include "Service/updateservice.h"

int main(int argc, char *argv[])
{
    QGuiApplication g_app(argc, argv);
    
    NetService *g_t_net = new NetService;
    SqlService *g_t_sql = new SqlService;
    UpdateService *g_t_update = new UpdateService;
    ContrlService *g_t_control = new ContrlService(g_t_net,g_t_sql,g_t_update);

    g_t_net->start();
    g_t_sql->start();
    g_t_update->start();
    g_t_control->start();

    QQmlApplicationEngine g_engine;
    g_engine.rootContext()->setContextProperty("g_t_control", g_t_control);
    QObject::connect(
        &g_engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &g_app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    g_engine.load(QUrl("qrc:/Main.qml"));

    return g_app.exec();
}
