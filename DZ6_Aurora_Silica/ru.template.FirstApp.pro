TARGET = ru.template.FirstApp

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \

HEADERS += \

DISTFILES += \
    qml/pages/SecondPage.qml \
    rpm/ru.template.FirstApp.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.FirstApp.ts \
    translations/ru.template.FirstApp-ru.ts \
