#include "mainwindow.h"

#include <QApplication>

#include "vehiclecontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    VehicleControl vcu;

    QObject::connect(&w, SIGNAL(Signal_Changed_StartSwitch(qint8)), &vcu,
    SLOT(Slot_SetVehicleState(qint8)));

    QObject::connect(&w, SIGNAL(Signal_Changed_GasPedal(bool)), &vcu,
    SLOT(Slot_Changed_GasPedal(bool)));

    QObject::connect(&w, SIGNAL(Signal_Changed_StopPedal(bool)), &vcu,
    SLOT(Slot_Changed_StopPedal(bool)));

    QObject::connect(&w, SIGNAL(Signal_Changed_GearSelector(qint8)), &vcu,
    SLOT(Slot_SetGearWheel(qint8)));

    QObject::connect(&vcu, SIGNAL(Signal_EngineRevolutions(qreal)), &w,
    SLOT(Slot_SetValueTachometerByRelationUnits(qreal)));

    QObject::connect(&vcu, SIGNAL(Signal_VehicleSpeed(qreal)), &w,
    SLOT(Slot_SetValueSpeedometerByRelationUnits(qreal)));


    w.show();
    return a.exec();
}
