#include "..\include\backend.h"
#include "..\forDebug\loggingCategories.h"
#include "..\include\telemetryHandler.h"


//№№№  Backend - осуществляет взаимодействие между сетью, командами и GUI.
// Для корректной работы Backend необходимо установить NetworkController иначе ошибка RC::NetworkControllerError
// После установки NetworkController  с помощью setNetworkController или в конструкторе класса
// необходимо запустить функцию initAndStart(), в процессе выполнения которой будут соединениы все необходимые
// сигналы и слоты для взаимодествия с NetworkController, будут созданы RunningTimeContoller (усправление временем наработки оборудования),
// OperatingModeController (управление обработкой телемтрии для определения вышедших на рабочий режим комплектов),
// TelemetryHandler (обработчик телеметрии для обработки сырых данных).
// Ошибку в работе класса можно определить с помощью функции errorCode().

Backend::Backend(QObject *parent) :
    QObject(parent)
{
    mp_backFrontBridge = new BackFrontBridge();
}

Backend::Backend(NetworkController &networkController, QObject *parent):
    QObject(parent)
{
    mp_backFrontBridge = new BackFrontBridge();
    setNetworkController(networkController);
}

// setNetworkController() - Установить NetworkController.
void Backend::setNetworkController(NetworkController &networkController)
{
    if(mp_networkController == nullptr)
        mp_networkController = &networkController;
    if (errorCodeIncludes(RC::ErrorCode::NetworkControllerError)){
        removeErrorCode(RC::ErrorCode::NetworkControllerError);
    }
}

// getBackFrontBridge() - Получить объект моста между GUI и Backend
BackFrontBridge &Backend::getBackFrontBridge()
{

    return *mp_backFrontBridge;
}

// initAndStart() - Инициализация и старт. Соединяются все необходимые сигналы. При любом исходе выполнения функции
// инициализация считается пройденной, после этого значение errorCode не будет содержать ошибку инициализации.
void Backend::initAndStart()
{
    if (errorCodeIncludes(RC::ErrorCode::NetworkControllerError) == false){
        connect(this, &Backend::commandChanged, mp_networkController, &NetworkController::sendData);
        connect(mp_networkController, &NetworkController::dataReceived, this, &Backend::handleTelematry);
        connect(mp_networkController, &NetworkController::errorCodeChanged, this, &Backend::handleErrorCode);
        connect(mp_networkController, &NetworkController::connectedStateChanged, this, &Backend::handleConnectedState);
        connect(mp_backFrontBridge, &BackFrontBridge::tryConnect, mp_networkController, &NetworkController::tryConnect);
    }

    connect(&m_telemetryHandler, &TelemetryHandler::newTelemetry, this, &Backend::setNewTelemetry);
    m_timerTelemetry.setInterval(RC::_TELEMETRY_TIME_REQUEST_PERIOD);
    connect(&m_timerTelemetry, &QTimer::timeout, this, &Backend::updateTelemetry);

    m_operatingModeController.initAndStart();

    connect(&m_runningTimeController, &RunningTimeContoller::requestedRunningTime, this, &Backend::requestRunningTime);
    m_runningTimeController.initAndStart();
    //  соединение активируется когда передается новая команда
    connect(mp_backFrontBridge, &BackFrontBridge::commandChanged, this, &Backend::newCommandCode);
    connect(this, &Backend::newErrorString, mp_backFrontBridge, &BackFrontBridge::setErrorString);

    removeErrorCode(RC::ErrorCode::NotInit);

    connect(this, &Backend::errorCodeChanged, this, &Backend::showError);
    showError();

}

QByteArray Backend::command() const
{
    return m_command;
}

RC::ErrorCode Backend::errorCode() const
{
    return m_errorCode;
}

// addErrorCode() - Доабвить новый код ошибки addErrorCode в переменную errorCode
void Backend::addErrorCode(RC::ErrorCode addErrorCode)
{
    m_errorCode = static_cast<RC::ErrorCode>(
                static_cast<quint32>(m_errorCode) |
                static_cast<quint32>(addErrorCode));
}

// removeErrorCode() - Удалить код ошибки rmErrorCode из переменной errorCode
void Backend::removeErrorCode(RC::ErrorCode rmErrorCode)
{
    RC::ErrorCode newErrorCode = static_cast<RC::ErrorCode>(
            static_cast<quint32>(errorCode()) &
            (~static_cast<quint32>(rmErrorCode)));

    setErrorCode(newErrorCode);
}

// errorCodeIncludes() - Проверить входит ли код ошибки inclErrorCode в переменную errorCode
quint8 Backend::errorCodeIncludes(RC::ErrorCode inclErrorCode)
{
    quint8 isIncludes = RC::_FALSE;
    if (static_cast<quint32>(errorCode()) & static_cast<quint32>(inclErrorCode))
        isIncludes = RC::_TRUE;
    return isIncludes;
}

// handleTelematry() - Обработать телеметрию из сырых данных
void Backend::handleTelematry(QByteArray rawData)
{
    m_telemetryHandler.setRawData(rawData);
    m_telemetryHandler.parseTelemetry();
}

// handleErrorCode() - Обработать код ошибки - составить строку ошибки и спустить сигнал newErrorString.
void Backend::handleErrorCode(RC::ErrorCode errorCode)
{
    switch (errorCode) {
    case RC::ErrorCode::WrongConfig:
        newErrorString("Ошибка файла конфигурации");
        break;
    case RC::ErrorCode::NetError:
        newErrorString("Ошибка подключения по сети");
        break;
    case RC::ErrorCode::NotError:
        newErrorString("");
        break;
    default:
        break;
    }

}

// handleErrorCode() - Запросить время наработки
void Backend::requestRunningTime()
{
    newCommandCode(Protocol::_Request_TIME);
}

// handleErrorCode() - Запросить время наработки
void Backend::requestTelemetry()
{
    qDebug(logDebug()) << Q_FUNC_INFO;
    newCommandCode(Protocol::_Request_TELEM);
}

// setCommand() - установить новую команду (вкл./откл., запросить время наработки, запросить телеметрию)
void Backend::setCommand(QByteArray command)
{
    if (command != Protocol::_Request_TELEM)
        m_timerTelemetry.stop();

    m_command = command;
    emit commandChanged(m_command);

    if (command != Protocol::_Request_TELEM)
        m_timerTelemetry.start();
}

void Backend::updateTelemetry()
{
    requestTelemetry();
}

// newCommandCode() - получить код команды и установить его
void Backend::newCommandCode(QString commandName)
{
    setCommand(m_commandBase.commandPair(commandName).second);
}

// handleConnectedState() - Обработать состояние сети, после подключения автоматически запрашивается телеметрия
// и запускается таймер периодческого запроса телеметрии.
void Backend::handleConnectedState(quint8 connectedState)
{
    mp_backFrontBridge->setConnected(connectedState);
    if (connectedState){
        requestRunningTime();
        m_timerTelemetry.start();
    }
    else
        m_timerTelemetry.stop();
}

// showError() - Показать ошибки при их наличии.
void Backend::showError()
{
    // если инициализация началась (т.е. запущено initAndStart), то при последующих изменениях кода ошибки будет выведено сообщение
    if (errorCode() != RC::ErrorCode::NotError){
        if (errorCodeIncludes(RC::ErrorCode::NetworkControllerError))
            qInfo(logInfo()) << "Error : NetworkControllerError";
        if (errorCodeIncludes(RC::ErrorCode::NotInit))
            qInfo(logInfo()) << "Error : InitError";
    }
}

// setErrorCode() - Установить код ошибки в переменную errorCode. Если вы хотите добавить код ошибки к уже имеющимся ошибкам -
// используйте addErrorCode(RC::ErrorCode)
void Backend::setErrorCode(const RC::ErrorCode errorCode)
{
    if (m_errorCode == errorCode)
        return;

    m_errorCode = errorCode;
    emit errorCodeChanged(m_errorCode);
}

//  setNewTelemetry() - Установить новую телеметрию
void Backend::setNewTelemetry(QVariantMap telemetry)
{
    mp_backFrontBridge->setTelemetry(telemetry);
    if (telemetry[Protocol::_Last_Command].toString().indexOf(m_commandBase.command()[Protocol::_Request_TIME].toString()) < 0)
    {
        m_operatingModeController.checkOperatingMode(telemetry);
        mp_backFrontBridge->setHalfSetOpMode(m_operatingModeController.opModeHalfSet());
    }
}
