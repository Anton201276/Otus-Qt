#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gas_pedal->setText("Газ");
    ui->stop_pedal->setText("Стоп");

    ui->speedometer->setMaximum(300);
    ui->speedometer->setTextUnitsMeasure("км/ч");
    ui->tachometer->setMaximum(5000);
    ui->tachometer->setTextUnitsMeasure("об/мин");

    connect(ui->switch_start, &QCheckBox::stateChanged, this, &MainWindow::on_switch_start_stateChanged);
    connect(ui->gas_pedal, &QAbstractButton::pressed, this, &MainWindow::on_Pressed_GasPedal);
    connect(ui->gas_pedal, &QAbstractButton::released, this, &MainWindow::on_Released_GasPedal);
    connect(ui->stop_pedal, &QAbstractButton::pressed, this, &MainWindow::on_Pressed_StopPedal);
    connect(ui->stop_pedal, &QAbstractButton::released, this, &MainWindow::on_Released_StopPedal);
    connect(ui->gear_selector, &QSlider::valueChanged, this, &MainWindow::on_Changed_GearSelector);

    ui->lbl_help->setStyleSheet("background-color: rgb(98, 98, 98); color:#FFF61F;");
    ui->lbl_help->setText("Нажмите кнопку \"ВКЛ\"");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_switch_start_stateChanged(int arg1) {
    if (arg1 == Qt::Unchecked) {
        ui->speedometer->setEnabled(false);
        ui->tachometer->setEnabled(false);
        ui->lbl_help->setStyleSheet("background-color: rgb(120, 120, 120); color:#FFF61F;");
        ui->lbl_help->setText("Нажмите кнопку \"ВКЛ\"");
    }
    else if (arg1 == Qt::PartiallyChecked) {
        ui->speedometer->setEnabled(true);
        ui->tachometer->setEnabled(true);
        ui->lbl_help->setStyleSheet("background-color: rgb(120, 120, 120); color:#55FA3E;");
        ui->lbl_help->setText("Нажмите кнопку \"СТАРТ\"");
    }
    else {
        ui->lbl_help->setStyleSheet("background-color: rgb(120, 120, 120); color:#2540D9;");
        ui->lbl_help->setText("\"Газ\" - увелиить, \"Стоп\" - убавить,  \"ОТКЛ\" - выключить");
    }

    emit Signal_Changed_StartSwitch(arg1);
}

void MainWindow::Slot_SetValueTachometerByRelationUnits(double val){
    int value = (int)(ui->tachometer->maximum() * val);
    ui->tachometer->setValue(value);
    return;
}

void MainWindow::Slot_SetValueSpeedometerByRelationUnits(double val){
    int value = (int)(ui->speedometer->maximum() * val);
    ui->speedometer->setValue(value);
    return;
}

void MainWindow::on_Pressed_GasPedal() {
    emit Signal_Changed_GasPedal(true);
}

void MainWindow::on_Pressed_StopPedal(){
    emit Signal_Changed_StopPedal(true);
}

void MainWindow::on_Changed_GearSelector(){
    emit Signal_Changed_GearSelector(ui->gear_selector->value());
}

void MainWindow::on_Released_GasPedal() {
    emit Signal_Changed_GasPedal(false);
}

void MainWindow::on_Released_StopPedal() {
    emit Signal_Changed_StopPedal(false);
}
