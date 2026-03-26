#ifndef CONTROLSIMULATOR_H
#define CONTROLSIMULATOR_H

#include <QObject>
#include <QString>
#include <QDebug>

class ControlSimulator : public QObject
{
    Q_OBJECT
public:
    explicit ControlSimulator(QObject *parent = nullptr);

public slots:  // 4. Слоты для вызова из QML
    void onMessageReceived(const QString &message) {
        qDebug() << "Получено сообщение из QML:" << message << "\n";
    }

    void onDataReceived(const QString &name, int age) {
        qDebug() << "Получены данные из QML::" << name << ", возраст:" << age;
    }

signals:  // 5. Сигналы для обратной связи (опционально)
    void messageSent(const QString &response);
    void dataProcessed(const QString &status);

};

#endif // CONTROLSIMULATOR_H
