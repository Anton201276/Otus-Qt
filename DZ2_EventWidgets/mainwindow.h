#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Slot_SetValueTachometerByRelationUnits(qreal  val);
    void Slot_SetValueSpeedometerByRelationUnits(qreal  val);

signals:
   void Signal_Changed_StartSwitch(qint8  arg1);
   void Signal_Changed_GasPedal(bool  cgp);
   void Signal_Changed_StopPedal(bool  csp);
   void Signal_Changed_GearSelector(qint8  gear);

private slots:
    void on_switch_start_stateChanged(int arg1);
    void on_Pressed_GasPedal();
    void on_Pressed_StopPedal();
    void on_Released_GasPedal();
    void on_Released_StopPedal();
    void on_Changed_GearSelector();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
