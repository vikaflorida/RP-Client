QT += quick network qml

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    source/backfrontbridge.cpp \
    source/backend.cpp \
    source/telemetryhandler.cpp \
    source/networkcontroller.cpp \
    forDebug/loggingcategories.cpp \
    forDebug/logger.cpp \
    source/rc.cpp \
    source/protocol.cpp \
    source/operatingmodecontroller.cpp \
    source/runningtimecontoller.cpp \
    rpclient.cpp

RESOURCES += \
    design/qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/backfrontbridge.h \
    include/backend.h \
    include/telemetryhandler.h \
    include/networkcontroller.h \
    forDebug/loggingcategories.h \
    include/rc.h \
    forDebug/logger.h \
    include/protocol.h \
    include/operatingmodecontroller.h \
    include/runningtimecontoller.h \
    rpclient.h
