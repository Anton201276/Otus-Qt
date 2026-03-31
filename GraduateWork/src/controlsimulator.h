#ifndef CONTROLSIMULATOR_H
#define CONTROLSIMULATOR_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTimer>

#include "sokrat3_db.h"

class ControlSimulator : public QObject
{
    Q_OBJECT
public:
    explicit ControlSimulator(QObject *parent = nullptr);
    ~ControlSimulator();

    Q_INVOKABLE int invoke_execute_QueryDB_ByName(const QString& db_Name);
    Q_INVOKABLE QVariant invoke_get_Value_ByIndex(int, const QString&);

    Q_INVOKABLE int invoke_model_position();
    Q_INVOKABLE int invoke_model_state();

public slots:  // 4. Слоты для вызова из QML
    void slot_onMessageReceived(const QString &message);
    void slot_onDataReceived(const QString &name, int age);
    void slot_onDriveSetPosition(int setpos);

signals:  // 5. Сигналы для обратной связи (опционально)
    void signal_messageSent(const QString &response);
    void signal_dataProcessed(const QString &status);



private:
    struct modelStructire {
        int cmd = 0;
        int prevCmd = 0;
        int position = 500;
        int dest_position = -1;
        int state = 0;
        int delta_pos = 20;
        int step_pos_model = 5;
        int step_pos_move = step_pos_model;
        int timer_tick = 50;
    };

    void upDateStateByCommand(int setpos);
    void onTimoutSimulateModelCalc();

private:
    Sokrat3_DB* mySokratDB_;
    QTimer* timer_;

    modelStructire sModelValve_;
};



#endif // CONTROLSIMULATOR_H
