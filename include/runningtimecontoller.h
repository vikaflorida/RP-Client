#ifndef RUNNINGTIMECONTOLLER_H
#define RUNNINGTIMECONTOLLER_H

#include <QTimer>
#include <QObject>

// RunningTimeContoller - Контроллер Времени наработки.
class RunningTimeContoller : public QObject
{
    Q_OBJECT
public:
private:
    QTimer m_timer;

public:
    explicit RunningTimeContoller(QObject *parent = nullptr);
    void initAndStart();

private:

private slots:
    void getTime();

public slots:

signals:
    void requestedRunningTime();
};

#endif // RUNNINGTIMECONTOLLER_H
