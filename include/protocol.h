#ifndef TP_H
#define TP_H
#include <QObject>
#include <QMap>
#include <QVariant>
#include <QStandardPaths>

namespace Protocol {
Q_NAMESPACE

enum ReceiptErrorCode{
    NotError = 0b0000,
    CommandError = 0b0010
};

enum Format{
    Bit,
    Byte
};

enum Type{
    Int,                //  Int                 -   целое число - max 4 byte quint32
    Bool,               //  Bool                -   булева переменная - max 4 byte quint32
    StringInByteArray,  //  StringInByteArray   -   строка записанная кодами байт в соответствии с UTF8
    Real_7e4            //  Real_7e4            -   нецелое число с целой частью, которая описыватся 7 двоичными разрядами
                        //                          и дробной частью, которая описывается 4 двоиными разрядами (2 байта на всё число)
};


// Константы, которые необходимы для составления ключей полей телеметрии
static const quint8 _KIT_1_COUNT = 2; // Количество комплектов №1
static const quint8 _KIT_2_COUNT = 2; // Количество комплектов №2

static const QString _KIT_1 = "Kit1";
static const QString _KIT_2 = "Kit2";
static const QString _KIT_3 = "Kit3";

static const QString _KIT_C = "KitC";
static const QString _KIT_V = "KitV";

static const QString _TELEM = "TELEM";
static const QString _TIME = "TIME";

static const QString _Code_Error_ = "Code_Error_";
static const QString _Hourse_ = "Hourse_";
static const QString _Minutes_ = "Minutes_";

static const QString __1 = "_1";
static const QString __2 = "_2";

static const QString _KIT_1_1 = _KIT_1 + __1;
static const QString _KIT_1_2 = _KIT_1 + __2;
static const QString _KIT_2_1 = _KIT_2 + __1;
static const QString _KIT_2_2 = _KIT_2 + __2;

static const QString __ON = "_ON";
static const QString __OFF = "_OFF";

static const QString _Identif = "Identif";
static const QString _Temperature_ = "Temperature_";
static const QString _Current_ = "Current_";

static const QString _Last_Command = "Last_Command";

// Ключи полей телеметрии
static const QString _Temperature_KIT_2 = _Temperature_ + _KIT_2;
static const QString _Current_KIT_2 = _Current_ + _KIT_2;

static const QString _Temperature_KIT_1 = _Temperature_ + _KIT_1;
static const QString _Current_KIT_1 = _Current_ + _KIT_1;

static const QString _Temperature_KIT_3 = _Temperature_ + _KIT_3;
static const QString _Temperature_C = _Temperature_ + _KIT_C;

static const QString _Current_V = _Current_ + _KIT_V;

static const QString _KIT_2_1_ON = _KIT_2_1 + __ON;
static const QString _KIT_2_2_ON = _KIT_2_2 + __ON;
static const QString _KIT_1_1_ON = _KIT_1_1 + __ON;
static const QString _KIT_1_2_ON = _KIT_1_2 + __ON;
static const QString _KIT_V_ON  = _KIT_V + __ON;

static const QString _Code_Error_TELEM = _Code_Error_ + _TELEM;
static const QString _Code_Error_TIME =  _Code_Error_ + _TIME;
static const QString _Hourse_TIME =  _Hourse_ + _TIME;
static const QString _Minutes_TIME =  _Minutes_ + _TIME;


// Константы, которые необходимы для составления ключей полей комманд
static const QString __HalfSet =  "_HalfSet";
static const QString __VKL =  "_VKL";
static const QString __OTK =  "_OTK";
static const QString _Request_ =  "Request_";
static const QString _IS_ =  "IS_";
static const QString _ALL = "ALL";

// Ключи команд
static const QString _KIT_1_1_ON_COM   =  _KIT_1 + __HalfSet + __1 + __ON;
static const QString _KIT_1_1_OFF_COM  =  _KIT_1 + __HalfSet + __1 + __OFF;
static const QString _KIT_1_2_ON_COM   =  _KIT_1 + __HalfSet + __2 + __ON;
static const QString _KIT_1_2_OFF_COM   =  _KIT_1 + __HalfSet + __2 + __OFF;

static const QString _KIT_2_1_ON_COM   =  _KIT_2 + __HalfSet + __1 + __ON;
static const QString _KIT_2_1_OFF_COM  =  _KIT_2 + __HalfSet + __1 + __OFF;
static const QString _KIT_2_2_ON_COM   =  _KIT_2 + __HalfSet + __2 + __ON;
static const QString _KIT_2_2_OFF_COM  =  _KIT_2 + __HalfSet + __2 + __OFF;

static const QString _KIT_1_KIT_2_OFF  =  _KIT_1 + "_" + _KIT_2 + __OFF;
static const QString _Request_TELEM  =  _Request_ + _TELEM;
static const QString _Request_TIME  =  _Request_ + _TIME;

// Значения команд
static const QString _KIT_1_1_IS_ON  =  _KIT_1 + __VKL + __1;
static const QString _KIT_1_1_IS_OFF  =  _KIT_1 + __OTK + __1;
static const QString _KIT_1_2_IS_ON  =  _KIT_1 + __VKL + __2;
static const QString _KIT_1_2_IS_OFF  =  _KIT_1 + __OTK + __2;
static const QString _KIT_2_1_IS_ON  =  _KIT_2 + __VKL + __1;
static const QString _KIT_2_1_IS_OFF  =  _KIT_2 + __OTK + __1;
static const QString _KIT_2_2_IS_ON  =  _KIT_2 + __VKL + __2;
static const QString _KIT_2_2_IS_OFF  =  _KIT_2 + __OTK + __2;
static const QString _ALL_OFF   =  _ALL + __OTK;
static const QString _IS_TELEM  =  _IS_ + _TELEM;
static const QString _IS_TIME   =  _IS_ + _TIME;


static const quint32 _HALFSET_SOURCE_COUNT = 3; // Количество источников в комплекте
static const quint32 _COMMAND_FIRST_BYTE = 2;   // Номер байта с которого начинается команда в квитанции
static const quint32 _COMMAND_BYTE_COUNT = 10;  // Количество байт отведенных для поля команды в байтовом массиве телеметрии

static const quint32 _BYTE_SIZE = 8;            // Количество бит в байте

static const quint32 _MAX_WHOLE_REAL_7E4 = 127; // Максимальное целое в числе формата REAL_7E4
static const quint32 _ACCUR_DEC_REAL_7E4 = 10;  // Точность округления REAL_7E4 - до десятых( до 10 доли т.е. 0.1)
static const quint32 _REAL_7E4_BYTE_COUNT = 2;  // Количство байт в числе REAL_7E4

static const quint32 _RECEIPT_WITH_TELEM_BYTE_COUNT = 70;   // Количество байт в ответвной квитанции, содержащей телеметрии
static const quint32 _RECEIPT_WITHOUT_TELEM_BYTE_COUNT = 18;// Количество байт в ответвной квитанции, содержащей время наработки


static const quint32 _IDENTIF_RECEIPT = 0x10;               // Поле идентификатора команды в сооотвествии с протоклом

static const quint32 _RUNNING_TIME_UPDATE_INTERVAL = 1000 * 60 * 5; // ms. Интервал обновления времени наработки

static const QString _HOME_DIR = "../config/";          // Путь к домашней "дирректории" - где хранится папка конфигурации
static const QString _CONFIG_DIR = _HOME_DIR + "";      // Путь к дирректории конфигурации

static const QString _CONFIG_BOARD_FILE_NAME = _CONFIG_DIR + "configBoard.config";          // Имя файла настройки платы - содержит адреса датчиков, двоиные коды для управления по I2C и пр.
static const QString _CONFIG_NET_FILE_NAME = _CONFIG_DIR + "configRP.config";            // Имя файла сетевой конфигурации RP - содержит порт и IP
static const QString _CONFIG_OVERHEATING_FILE_NAME = _CONFIG_DIR + "configOverTemp.config"; // Имя файла содержащего информацию о температури, при которой необходимо отключить все (т.е. если что-то перегреется).

static const QString _CONFIG_OP_MODE_FILE_NAME = _CONFIG_DIR + "configOpMode.config";       // Имя файла содержащего информацию о температуре и о допуске температуры выхода на рабочий режим

// Ключи настроек выхода на рабочий режим для соотвтсвующего файла
static const QString _file_TEMP_OPERATING_MODE_KIT_2 = "TEMP_OPERATING_MODE_KIT_2";
static const QString _file_TOLERANCE = "TOLERANCE";

static const QString _RT_DIR = _HOME_DIR + "/RT/";      // Путь к дирректории c файлом времени наработки
static const QString _RT_FILE_NAME = _RT_DIR + "RT.dat";// Имя файла содержащего информацию о времени наработки

class FormatFirstSizeType{
public:
    FormatFirstSizeType() {}
    FormatFirstSizeType(Format format, quint32 first, quint32 size, Type type)
    {
        this->format = format;
        this->first = first;
        this->size = size;
        this->type = type;
    }
    Format format;
    quint32 first;
    quint32 size;
    Type type;
    QVariant toQVariant();
};

class TelemetryProtocol{
    QMap<QString, FormatFirstSizeType> m_telemetryProtocol;
public:
    TelemetryProtocol();
    QMap<QString, FormatFirstSizeType> telemetryProtocol();
    QMap<QString, QVariant> telemetryProtocol_Q();
};

class CommandProtocol{
    QVariantMap m_commandProtocol;
public:
    CommandProtocol();
    QVariantMap commandProtocol();
};

}
#endif // TP_H
