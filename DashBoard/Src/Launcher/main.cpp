#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication g_app(argc, argv);

    QQmlApplicationEngine g_engine;
    QObject::connect(
        &g_engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &g_app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    g_engine.loadFromModule("Launcher", "Main");

    return g_app.exec();
}
