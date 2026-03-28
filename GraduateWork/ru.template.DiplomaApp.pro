TARGET = ru.template.DiplomaApp

QT += sql

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/controlsimulator.cpp \
    src/main.cpp \
    src/sokrat3_db.cpp

HEADERS += \
    src/controlsimulator.h \
    src/sokrat3_db.h

DISTFILES += \
    qml/pages/ConnectSettings.qml \
    qml/pages/ControlPage.qml \
    qml/pages/SimulationModelDriver.qml \
    qml/pages/UserParamsPage.qml \
    rpm/ru.template.DiplomaApp.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.DiplomaApp.ts \
    translations/ru.template.DiplomaApp-ru.ts \
