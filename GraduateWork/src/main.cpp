#include <auroraapp.h>
#include <QtQuick>

#include "controlsimulator.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.template"));
    application->setApplicationName(QStringLiteral("DiplomaApp"));

    ControlSimulator controlSim;
    QScopedPointer<QQuickView> view(Aurora::Application::createView());

    // Получаем базовый путь OfflineStorage
    QString basePath = view->engine()->offlineStoragePath();
    qDebug() << "OfflineStorage path:" << basePath;

    // Формируем полный путь к папке Databases
    QString databasesPath = basePath + "/Databases";
    qDebug() << "Databases directory:" << databasesPath;




    // ВАЖНО: устанавливаем свойство контекста ДО загрузки QML
    view->engine()->rootContext()->setContextProperty("controlSim", &controlSim);

    // Регистрируем тип для использования в QML
    //qmlRegisterType<ControlSimulator>("ru.template.DiplomaApp", 1, 0, "MyHandler");

    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/DiplomaApp.qml")));


    if (!view->rootObject()) {
            qCritical() << "Не удалось загрузить QML-файл";
            return -1;
    }

    // Получаем корневой объект QML
    QObject *rootObject = view->rootObject();

        // Подключаем сигнал QML к слоту C++
    QObject::connect(rootObject, SIGNAL(dataSent(QString,int)),
                        &controlSim, SLOT(slot_onDataReceived(QString,int)));

    QObject::connect(rootObject, SIGNAL(messageSent(QString)),
                        &controlSim, SLOT(slot_onMessageReceived(QString)));





    view->show();

    return application->exec();
}
