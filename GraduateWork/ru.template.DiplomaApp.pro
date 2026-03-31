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
    qml/pages/AnalogIndicator.qml \
    qml/pages/ConnectSettingsPage.qml \
    qml/pages/ControlPage.qml \
    qml/PlantParamsPage.qml \
    qml/pages/ListModelValue.qml \
    qml/pages/SimulationModelPage.qml \
    qml/pages/UserParamsPage.qml \
    qml/pages/ValveStatusBar.qml \
    rpm/ru.template.DiplomaApp.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.DiplomaApp.ts \
    translations/ru.template.DiplomaApp-ru.ts \

RESOURCES += \
    resources.qrc
