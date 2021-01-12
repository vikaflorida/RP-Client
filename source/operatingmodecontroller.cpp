#include "../include/operatingmodecontroller.h"
#include "../forDebug/loggingCategories.h"
#include <QFile>

// ВНИМАНИЕ! Класс полностью привязан к соответсвующей аппаратуре.

// OperatingModeController - Контроллер Рабочего Режима - Обрабатывает данные телеметрии и определяет
// в соответствии с файлом настройки рабочего режима вышел ли комплект на раюочий режим или нет.
OperatingModeController::OperatingModeController(QObject *parent) : QObject(parent)
{

}

// initAndStart() - Инициализация и старт. После инициализации все комплекты считаются на вышедшими на рабочий режим.
// Запускается функция получения параметров выхода на рабочий режим из файла настроек Protocol::_CONFIG_OP_MODE_FILE_NAME.
void OperatingModeController::initAndStart()
{
    setConfiguration();
    m_opModeHalfSet[Protocol::_KIT_2_1] = RC::_FALSE;
    m_opModeHalfSet[Protocol::_KIT_2_2] = RC::_FALSE;
}

// initAndStart() - Проверить по телеметрии вышел ли комплект на рабочий режим.
void OperatingModeController::checkOperatingMode(QVariantMap telemetry)
{
    m_opModeSource.clear();
    if (errorCode() == RC::ErrorCode::NotError){
        QVariantMap::iterator telemetryIterator = telemetry.begin();
        // определить необходимые температуры
        while (telemetryIterator != telemetry.end())
        {
            QString key(telemetryIterator.key());
            if (key.indexOf(Protocol::_Temperature_KIT_2) >= 0)
            {
                QString tempStr = telemetry[telemetryIterator.key()].toString();
                qreal temparature = (tempStr.toDouble());
                if ( temparature >= (m_temperature - m_tolerance))
                {
                    if (temparature <= (m_temperature + m_tolerance))
                    {
                        m_opModeSource.push_back(telemetryIterator.key());
                    }
                    else
                    {
                        m_overOpModeSource.push_back(telemetryIterator.key());
                    }
                }
            }
            telemetryIterator++;
        }
        // установить какие полукоплекты вышли на рабочий режим
        detectOperatingModeHalfSets();
    }
}

// opModeHalfSet() - Вернуть карту, которая содержит данные о том вышли ли на рабочий режим комплекты.
QVariantMap OperatingModeController::opModeHalfSet() const
{
    return m_opModeHalfSet;
}

// errorCode() - Вернуть код ошибки errorCode.
RC::ErrorCode OperatingModeController::errorCode() const
{
    return m_errorCode;
}

// setConfiguration() - установить конфиграцию контроллера, т.е установить параметры выхода на рабочий режим из файла настроек.
void OperatingModeController::setConfiguration()
{
    setErrorCode(RC::ErrorCode::NotError);

    QFile configFile(m_configFileName);
    if (!configFile.open(QIODevice::ReadOnly)){
        setErrorCode(RC::ErrorCode::WrongConfig);
    }
    else{
        QString tmp = QString::fromUtf8(configFile.readAll());
        QStringList splitStrings;
        splitStrings = tmp.split("\r\n");

        QStringList values;
        for (QString string: splitStrings)
            values.append(string.split(":"));

        int indexOfTemp = values.indexOf(Protocol::_file_TEMP_OPERATING_MODE_KIT_2) + 1;
        setTemperatureOperatingMode(values.at(indexOfTemp));

        int indexOfTolerance = values.indexOf(Protocol::_file_TOLERANCE) + 1;
        setToleranceOperatingMode(values.at(indexOfTolerance));

        qInfo(logInfo()) << "Температура выхода на рабочий режим:  \t" << m_temperature;
        qInfo(logInfo()) << "Допуск температуры:  \t" << m_tolerance;
    }

}

// setTemperatureOperatingMode() - Установить температуру выхода на рабочий режим.
void OperatingModeController::setTemperatureOperatingMode(QString temperature)
{
    m_temperature = temperature.toDouble();
}

// setToleranceOperatingMode() - Установить допуск температуры выхода на рабочий режим.
void OperatingModeController::setToleranceOperatingMode(QString tolerance)
{
    m_tolerance = tolerance.toDouble();
}

// detectOperatingModeHalfSets() - Определить какие полукомплекты вышли на рабочий режим.
void OperatingModeController::detectOperatingModeHalfSets()
{
    quint32 kit1SourceCount = 0;
    quint32 kit2SourceCount = 0;
    for (quint32 i = 0; i < m_opModeSource.size(); i++){
        if (m_opModeSource.at(i).toString().indexOf(Protocol::_KIT_2 + "1") >= 0){
            kit1SourceCount++;
        }
        else if (m_opModeSource.at(i).toString().indexOf(Protocol::_KIT_2 + "2") >= 0){
            kit1SourceCount++;
        }
        else if (m_opModeSource.at(i).toString().indexOf(Protocol::_KIT_2 + "3") >= 0){
            kit1SourceCount++;
        }
        else if (m_opModeSource.at(i).toString().indexOf(Protocol::_KIT_2 + "4") >= 0){
            kit2SourceCount++;
        }
        else if (m_opModeSource.at(i).toString().indexOf(Protocol::_KIT_2 + "5") >= 0){
            kit2SourceCount++;
        }
        else if (m_opModeSource.at(i).toString().indexOf(Protocol::_KIT_2 + "6") >= 0){
            kit2SourceCount++;
        }
    }
    if (kit1SourceCount == Protocol::_HALFSET_SOURCE_COUNT)
        m_opModeHalfSet[Protocol::_KIT_2_1] = RC::_TRUE;
    else
        m_opModeHalfSet[Protocol::_KIT_2_1] = RC::_FALSE;

    if (kit2SourceCount == Protocol::_HALFSET_SOURCE_COUNT)
        m_opModeHalfSet[Protocol::_KIT_2_2] = RC::_TRUE;
    else
        m_opModeHalfSet[Protocol::_KIT_2_2] = RC::_FALSE;


    emit newOperatingModeHalfSets(m_opModeHalfSet);

}

// addErrorCode() - Доабвить новый код ошибки addErrorCode в переменную errorCode
void OperatingModeController::addErrorCode(RC::ErrorCode addErrorCode)
{
    m_errorCode = static_cast<RC::ErrorCode>(
                static_cast<quint32>(m_errorCode) |
                static_cast<quint32>(addErrorCode));
}

// removeErrorCode() - Удалить код ошибки rmErrorCode из переменной errorCode
void OperatingModeController::removeErrorCode(RC::ErrorCode rmErrorCode)
{
    RC::ErrorCode newErrorCode = static_cast<RC::ErrorCode>(
            static_cast<quint32>(errorCode()) &
            (~static_cast<quint32>(rmErrorCode)));

    setErrorCode(newErrorCode);
}

// errorCodeIncludes() - Проверить входит ли код ошибки inclErrorCode в переменную errorCode
quint8 OperatingModeController::errorCodeIncludes(RC::ErrorCode inclErrorCode)
{
    quint8 isIncludes = RC::_FALSE;
    if (static_cast<quint32>(errorCode()) & static_cast<quint32>(inclErrorCode))
        isIncludes = RC::_TRUE;
    return isIncludes;
}

//№№ showError() - Показать ошибки при их наличии.
void OperatingModeController::showError()
{
    // если инициализация началась (т.е. запущено initAndStart), то при изменении кода ошибки будет выведено сообщение
    if (errorCode() != RC::ErrorCode::NotError){
        if (errorCodeIncludes(RC::ErrorCode::WrongConfig))
            qInfo(logInfo()) << "Error : WrongConfigError";
        if (errorCodeIncludes(RC::ErrorCode::NotInit))
            qInfo(logInfo()) << "Error : InitError";
    }
}

// setErrorCode(RC::ErrorCode) - Установить код ошибки в переменную errorCode. Если вы хотите добавить код ошибки к уже имеющимся ошибкам -
// используйте addErrorCode(RC::ErrorCode)
void OperatingModeController::setErrorCode(const RC::ErrorCode errorCode)
{
    if (m_errorCode == errorCode)
        return;

    m_errorCode = errorCode;
    emit errorCodeChanged(errorCode);
}

