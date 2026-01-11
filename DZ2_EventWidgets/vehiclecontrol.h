#ifndef VEHICLECONTROL_H
#define VEHICLECONTROL_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class VehicleControl : public QObject
{
    enum VehicleState {
        vehicle_off = Qt::Unchecked,
        vehicle_on = Qt::PartiallyChecked,
        engine_on = Qt::Checked
    };

    const qint32 step_model_calc_msec = 10;
    const qint32 demo_seconds = 4;
    const qint32 max_demo_counter = demo_seconds * 1000 / (4 * step_model_calc_msec);
    const qreal step_calc = (double)step_model_calc_msec / 1000.0;

    const qreal ku_gas = 0.003;
    const qreal ku_stop = 0.005;
    const qreal ku_free = 0.001;
    const qreal gear_w[6]= {0.15, 0.0, 0.165, 0.36, 0.75, 1.0};
    const qreal min_gas_level = 0.16;

    enum DirectionCount {
        UpCount,
        DownCount
    };

    enum ControlStateVehicle {
        OffState,
        DemoState,
        RunEngine
    };

    Q_OBJECT
public:
    explicit VehicleControl(QObject *parent = nullptr){
        timer_ = new QTimer(this);
        timer_->setInterval(step_model_calc_msec);
        connect(timer_, &QTimer::timeout, this, &VehicleControl::onTimoutEngineModelCalc);
    }

    ~VehicleControl(){
        delete timer_;
    }

signals:
    void Signal_EngineRevolutions(qreal rel_unit);
    void Signal_VehicleSpeed(qreal rel_unit);

public slots:
    void Slot_SetGearWheel(qint8 gw) {
        gear_ = gear_w[gw + 1];
    }

    void Slot_SetVehicleState(qint8 vs) {
        switch (vs) {
            case vehicle_off:
                vehicle_state_ = OffState;
                timer_->stop();
                emit Signal_EngineRevolutions(0.0);
                emit Signal_VehicleSpeed(0.0);
                reset_vehicle_model();
                break;

            case vehicle_on:
                vehicle_state_ = DemoState;
                timer_->start();
                break;

            case engine_on:
                vehicle_state_ = RunEngine;
                gas_level_ = min_gas_level;
                timer_->start();
                break;
        }
    }

    void Slot_Changed_GasPedal(bool  cgp) {
        gas_pedal_ = cgp;
        counter_ = 0;
    }

    void Slot_Changed_StopPedal(bool  cgp) {
        stop_pedal_ = cgp;
        counter_ = 0;
    }

private slots:
    void onTimoutEngineModelCalc() {
        if (vehicle_state_ == DemoState) {
            demo_start_update();
        }
        else {
            calc_model_update();
        }
    }

private:
    void reset_vehicle_model() {
        vehicle_speed_= 0.0;
        engine_revolutions_ = 0.0;
        gear_ = 0;
        vehicle_state_ = OffState;
        dir_count_ = UpCount;
        counter_ = 0;
        timer_->stop();
    }

    void demo_start_update() {
        if (dir_count_ == UpCount) {
            if (counter_ >= max_demo_counter) {
                dir_count_ = DownCount;
                counter_ = max_demo_counter;
            }
            else {
                ++counter_;
            }

        }
        else {
            if (counter_ <= 0) {
                timer_->stop();
                dir_count_ = UpCount;
                counter_ = 0;
            }
            else {
                --counter_;
            }
        }
        emit Signal_EngineRevolutions(step_calc * counter_);
        emit Signal_VehicleSpeed(step_calc * counter_);
    }

    void calc_model_update() {
        if (gas_pedal_) {
            qreal tmp = gas_level_ + ku_gas * step_calc * counter_;
            gas_level_ = tmp > 1.0 ? 1.0 : tmp;
        }
        else if (stop_pedal_) {
            qreal tmp = gas_level_ - ku_stop * step_calc * counter_;
            gas_level_ = tmp <= 0.0 ? 0.0 : tmp;
        }
        else {
            qreal tmp = gas_level_ - ku_free * step_calc * counter_;
            gas_level_ = tmp <= min_gas_level ? min_gas_level : tmp;
        }
        emit Signal_EngineRevolutions(gas_level_);
        emit Signal_VehicleSpeed(gas_level_ * gear_);

        ++counter_;
    }

private:
    qreal vehicle_speed_= 0.0;
    qreal engine_revolutions_ = 0.0;
    qreal gear_ = 0.0;
    ControlStateVehicle vehicle_state_ = OffState;
    DirectionCount dir_count_ = UpCount;
    QTimer* timer_;
    qint32 counter_ = 0;
    qreal gas_level_ = 0.0;
    bool gas_pedal_ = false;
    bool stop_pedal_ = false;
};

#endif // VEHICLECONTROL_H
