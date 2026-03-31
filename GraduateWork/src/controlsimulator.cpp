#include "controlsimulator.h"

ControlSimulator::ControlSimulator(QObject *parent) : QObject(parent)
{
    mySokratDB_ = nullptr;

    timer_ = new QTimer(this);
    timer_->setInterval(sModelValve_.timer_tick);
    connect(timer_, &QTimer::timeout, this, &ControlSimulator::onTimoutSimulateModelCalc);
    timer_->stop();
}

ControlSimulator::~ControlSimulator() {
    delete timer_;
    delete mySokratDB_;
}

void ControlSimulator::slot_onMessageReceived(const QString &message) {
    qDebug() << "Получено сообщение из QML:" << message << "\n";
    if (mySokratDB_ == nullptr) {
        mySokratDB_ = new Sokrat3_DB(message);
        //emit Signal_GetDB_SokratDBModel(mySokratDB_);
    }

}

void ControlSimulator::slot_onDataReceived(const QString &name, int age) {
    qDebug() << "Получены данные из QML::" << name << ", номер:" << age;
}

int ControlSimulator::invoke_execute_QueryDB_ByName(const QString& db_Name) {
    return mySokratDB_->Execute_QueryDB_ByName(db_Name);
}

QVariant ControlSimulator::invoke_get_Value_ByIndex(int row, const QString& col) {
    return mySokratDB_->Get_Value_ByIndex(row, col);
}

void ControlSimulator::upDateStateByCommand(int setpos) {
    qDebug() << "Определяем статус";
    sModelValve_.dest_position = setpos;
    int set_delta_pos = sModelValve_.dest_position - sModelValve_.position;
    qDebug() << "Определяем статус" << sModelValve_.state << "  дельта = " <<set_delta_pos;
    switch (sModelValve_.state) {
    case 0: {
            if (set_delta_pos > sModelValve_.delta_pos) {
                timer_->start();
                sModelValve_.step_pos_move = sModelValve_.step_pos_model;
                sModelValve_.state = 3;
                qDebug() << "Статус из 1 - " << sModelValve_.state;timer_->start();
            }
            else if (set_delta_pos < -sModelValve_.delta_pos) {
                timer_->start();
                sModelValve_.step_pos_move = -sModelValve_.step_pos_model;
                sModelValve_.state = 4;
                qDebug() << "Статус из 1 - " << sModelValve_.state;
            }
        }
        break;

    case 1: {
            if (set_delta_pos < -sModelValve_.delta_pos) {
                timer_->start();
                sModelValve_.step_pos_move = -sModelValve_.step_pos_model;
                sModelValve_.state = 4;
                qDebug() << "Статус из 1 - " << sModelValve_.state;
            }
        }
        break;

    case 2: {
            if (set_delta_pos > sModelValve_.delta_pos) {
                timer_->start();
                sModelValve_.step_pos_move = sModelValve_.step_pos_model;
                sModelValve_.state = 3;
                qDebug() << "Статус из 2 - " << sModelValve_.state;
            }
        }
        break;

    case 3: {
            if (set_delta_pos < 0) {
                timer_->stop();
                sModelValve_.step_pos_move = 0;
                sModelValve_.state = 0;
                qDebug() << "Статус из 3 - " << sModelValve_.state;
            }
        }
        break;

    case 4: {
            if (set_delta_pos > 0) {
                timer_->stop();
                sModelValve_.step_pos_move = 0;
                sModelValve_.state = 0;
                qDebug() << "Статус из 4 - " << sModelValve_.state;
            }
        }
        break;
    }
}

void ControlSimulator::slot_onDriveSetPosition(int setpos) {
     qDebug() << "Получено новое положение из QML, положение = :" << setpos << "\n";
    upDateStateByCommand(setpos);
}

void ControlSimulator::onTimoutSimulateModelCalc() {

    //qDebug() << "Таймер C++ модели работает" ;

    if (sModelValve_.state == 3 || sModelValve_.state == 4) {
        sModelValve_.position += sModelValve_.step_pos_move;
    }

    //qDebug() << "Статус из в таймере - " << sModelValve_.state;
    //qDebug() << "Положение в моделе  = :" << sModelValve_.position << "\n";

    if (sModelValve_.position == sModelValve_.dest_position) {
        timer_->stop();
        if (sModelValve_.position >= 1000 - sModelValve_.step_pos_model) {
            sModelValve_.state = 1;
        }
        else if (sModelValve_.position < sModelValve_.step_pos_model) {
            sModelValve_.state = 2;
        }
        else {
            sModelValve_.state = 0;
        }
    }
    else if (sModelValve_.position >= sModelValve_.dest_position && sModelValve_.state == 3) {
        timer_->stop();
        sModelValve_.state = 0;
    }
    else if (sModelValve_.position <= sModelValve_.dest_position && sModelValve_.state == 4) {
        timer_->stop();
        sModelValve_.state = 0;
    }
    else if (sModelValve_.position >= 1000) {
        timer_->stop();
        sModelValve_.state = 1;
    }
    else if (sModelValve_.position <= 0) {
        timer_->stop();
        sModelValve_.state = 2;
    }
}

int ControlSimulator::invoke_model_position(){
   return  sModelValve_.position;
}

int ControlSimulator::invoke_model_state(){
    return sModelValve_.state;
}
