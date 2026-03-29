#ifndef CONTROLSIMULATOR_H
#define CONTROLSIMULATOR_H

#include <QObject>
#include <QString>
#include <QDebug>

#include "sokrat3_db.h"

class ControlSimulator : public QObject
{
    Q_OBJECT
public:
    explicit ControlSimulator(QObject *parent = nullptr);

    Q_INVOKABLE int invoke_execute_QueryDB_ByName(const QString& db_Name);
    Q_INVOKABLE QVariant invoke_get_Value_ByIndex(int, const QString&);

public slots:  // 4. Слоты для вызова из QML
    void slot_onMessageReceived(const QString &message);

    void slot_onDataReceived(const QString &name, int age);

signals:  // 5. Сигналы для обратной связи (опционально)
    void signal_messageSent(const QString &response);
    void signal_dataProcessed(const QString &status);

private:
    Sokrat3_DB* mySokratDB_;

};

#endif // CONTROLSIMULATOR_H
