#include "../include/runningtimecontoller.h"
#include "../include/rc.h"

// RunningTimeContoller - Контроллер Времени наработки. Организует запрос телеметрии с частатой,
// описанной периодом RC::_RUNNING_TIME_REQUEST_PERIOD.
RunningTimeContoller::RunningTimeContoller(QObject *parent) : QObject(parent)
{

}

// initAndStart() - Инициализация и старт. Запуск таймер с интервалом RC::_RUNNING_TIME_REQUEST_PERIOD,
// по таймауту будет происходить запрос телеметрии.
void RunningTimeContoller::initAndStart()
{
    m_timer.setInterval(RC::_RUNNING_TIME_REQUEST_PERIOD);
    connect(&m_timer, &QTimer::timeout, this, &RunningTimeContoller::getTime);
    m_timer.start();
}

// getTime() - Запрос времени.
void RunningTimeContoller::getTime()
{
    emit requestedRunningTime();
}
