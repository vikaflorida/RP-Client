#include "logger.h"
#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QDir>

QScopedPointer<QFile> m_logFile;
void messegeHandler(QtMsgType type, const QMessageLogContext & context, const QString &msg);

Logger::Logger()
{  
    QDir dataDir;
    dataDir.mkdir(m_logFilePath);
}

void Logger::initial()
{
    qInstallMessageHandler(messegeHandler);
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm_ss");
    m_logFileName = "log___RP_" + currentDateTime;
    m_logFileNameTXT = m_logFileName + ".txt";
    m_logFile.reset(new QFile(m_logFilePath + m_logFileNameTXT));
    m_logFile.data() -> open(QFile::Append | QFile::Text);
}

Logger::~Logger()
{
    m_logFile->close();

}

void messegeHandler(QtMsgType type, const QMessageLogContext & context, const QString &msg)
{
    QTextStream out(m_logFile.data());

    switch (type)
    {
    case QtInfoMsg:{
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz\t");
        out << context.category << ":\t" << msg << endl;
        out.flush();
        break;
    case QtDebugMsg:     {
            break;
        }
        case QtWarningMsg:
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz\t");
            out << context.category << ":\t" << msg << endl;
            break;
        case QtCriticalMsg:
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz\t");
            out << context.category << ":\t" << msg << endl;
            break;
        case QtFatalMsg:
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz\t");
            out << context.category << ":\t" << msg << endl;
            break;
        default:
            break;
        }
    }
    out.flush();
}
