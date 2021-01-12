#include "rpclient.h"

RPClient::RPClient(QObject * root, QObject * parent):
    QObject(parent)
{
    qRegisterMetaType<QHash<QString, QString>>();
    mp_root = root;
}

void RPClient::initAndStart()
{
    if (mp_root != nullptr)
    {
        m_networkController.initAndStart();

        mp_backend = new Backend(m_networkController, mp_root);
        mp_backend->initAndStart();
    }
}

BackFrontBridge &RPClient::getbackFrontBridge()
{
    return (mp_backend->getBackFrontBridge());
}
