#ifndef LOGGER_H
#define LOGGER_H
#include <QString>

class Logger
{
public:
    Logger();
    ~Logger();

    void initial();

private:
    QString m_logFilePath = "../log/";
    QString m_logFileName;
    QString m_logFileNameTXT;
};

#endif // LOGGER_H
