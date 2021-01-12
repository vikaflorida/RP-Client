#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>
#include <QObject>
#include "rpclient.h"
#include "forDebug/logger.h"

#define LOG_TO_FILE

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

#ifdef LOG_TO_FILE
    Logger logger;
    logger.initial();
#endif

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    QObject * root = engine.rootObjects()[0];

    RPClient rpClient(root);
    rpClient.initAndStart();
    engine.rootContext() -> setContextProperty("backFrontBridge", &rpClient.getbackFrontBridge());
    QQmlProperty(root, "startSetConnectionAndInitial").write(true);

    return app.exec();
}
