#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_equal, &QPushButton::clicked, this, &MainWindow::on_click_controll);
    connect(ui->btn_mem_recall, &QPushButton::clicked, this, &MainWindow::on_click_controll);
    connect(ui->btn_mem_clr, &QPushButton::clicked, this, &MainWindow::on_click_controll);
    connect(ui->btn_mem_store, &QPushButton::clicked, this, &MainWindow::on_click_controll);
    connect(ui->btn_clear, &QPushButton::clicked, this, &MainWindow::on_click_controll);
    connect(ui->btn_sign, &QPushButton::clicked, this, &MainWindow::on_click_controll);
    connect(ui->btn_chop, &QPushButton::clicked, this, &MainWindow::on_click_controll);
    connect(ui->btn_dot, &QPushButton::clicked, this, &MainWindow::on_click_controll);

    connect(ui->btn_dig_9, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_8, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_7, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_6, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_5, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_4, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_3, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_2, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_1, &QPushButton::clicked, this, &MainWindow::on_click_digit);
    connect(ui->btn_dig_0, &QPushButton::clicked, this, &MainWindow::on_click_digit);

    connect(ui->btn_div, &QPushButton::clicked, this, &MainWindow::on_click_operation);
    connect(ui->btn_pow, &QPushButton::clicked, this, &MainWindow::on_click_operation);
    connect(ui->btn_mult, &QPushButton::clicked, this, &MainWindow::on_click_operation);
    connect(ui->btn_plus, &QPushButton::clicked, this, &MainWindow::on_click_operation);
    connect(ui->btn_minus, &QPushButton::clicked, this, &MainWindow::on_click_operation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_click_digit() {
    QPushButton* pb = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(pb);

    QChar ch = pb->text()[0];
    Q_ASSERT(ch >= '0' && ch <='9');
    emit Signal_PressDigitalButton(ch);
}

void MainWindow::on_click_controll() {
    QObject* obj = sender();
    QWidget* wid = qobject_cast<QWidget*>(obj);

    if (wid == ui->btn_equal) {
        emit Signal_PressControlButton(ControlKey::EQUALS);
    }
    else if (wid == ui->btn_mem_recall) {
        emit Signal_PressControlButton(ControlKey::MEM_LOAD);
    }
    else if (wid == ui->btn_mem_clr) {
        ui->btn_mem_clr->setEnabled(false);
        ui->btn_mem_recall->setEnabled(false);
        emit Signal_PressControlButton(ControlKey::MEM_CLEAR);
    }
    else if (wid == ui->btn_mem_store) {
        ui->btn_mem_clr->setEnabled(true);
        ui->btn_mem_recall->setEnabled(true);
        emit Signal_PressControlButton(ControlKey::MEM_SAVE);
    }
    else if (wid == ui->btn_clear) {
        emit Signal_PressControlButton(ControlKey::CLEAR);
    }
    else if (wid == ui->btn_sign) {
        emit Signal_PressControlButton(ControlKey::PLUS_MINUS);
    }
    else if (wid == ui->btn_chop) {
        emit Signal_PressControlButton(ControlKey::BACKSPACE);
    }
    else {
        emit Signal_PressControlButton(ControlKey::DOT_KEY);
    }
}

void MainWindow::on_click_operation() {
    QObject* obj = sender();
    QWidget* wid = qobject_cast<QWidget*>(obj);

    if (wid == ui->btn_div) {
        emit Signal_PressOperetionButton(Operation::DIVISION);
    }
    else if (wid == ui->btn_plus) {
        emit Signal_PressOperetionButton(Operation::ADDITION);
    }
    else if (wid == ui->btn_pow) {
        emit Signal_PressOperetionButton(Operation::POWER);
    }
    else if (wid == ui->btn_minus) {
        emit Signal_PressOperetionButton(Operation::SUBTRACTION);
    }
    else {
        emit Signal_PressOperetionButton(Operation::MULTIPLICATION);
    }
}

void MainWindow::Slot_DisplayNumber(const QString& disnum) {
    ui->l_result->setText(disnum);
}

void MainWindow::Slot_DisplayMemory(const QChar dismem) {
    ui->l_memory->setText(dismem);
}
void MainWindow::Slot_DisplayFormula(const QString& disform) {
    ui->l_formula->setText(disform);
}
