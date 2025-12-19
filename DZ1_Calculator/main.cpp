#include "mainwindow.h"

#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Controller controller;

    QObject::connect(&w, SIGNAL(Signal_PressDigitalButton(QChar)), &controller,
    SLOT(Slot_ReciveDigitButton(QChar)));

    QObject::connect(&w, SIGNAL(Signal_PressControlButton(ControlKey)), &controller,
    SLOT(Slot_ReciveControllButton(ControlKey)));

    QObject::connect(&w, SIGNAL(Signal_PressOperetionButton(Operation)), &controller,
    SLOT(Slot_ReciveOperetionButton(Operation)));

    QObject::connect(&controller, SIGNAL(Signal_DisplayNumber(const QString&)), &w,
    SLOT(Slot_DisplayNumber(const QString&)));

    QObject::connect(&controller, SIGNAL(Signal_DisplayMemory(const QChar)), &w,
    SLOT(Slot_DisplayMemory(const QChar)));

    QObject::connect(&controller, SIGNAL(Signal_DisplayFormula(const QString&)), &w,
    SLOT(Slot_DisplayFormula(const QString&)));

    w.show();
    return a.exec();
}
