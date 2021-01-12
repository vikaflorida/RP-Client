#ifndef RPCLIENT_H
#define RPCLIENT_H
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>
#include <QObject>
#include "include/backend.h"
#include "include/backfrontbridge.h"
#include "include/networkcontroller.h"

class RPClient : public QObject
{
    Q_OBJECT
private:
    NetworkController m_networkController;
    Backend *mp_backend = nullptr;
    QObject * mp_root = nullptr;
public:
    explicit RPClient(QObject *root, QObject *parent = nullptr);
    void initAndStart();
    BackFrontBridge &getbackFrontBridge();
};

#endif // RPCLIENT_H
