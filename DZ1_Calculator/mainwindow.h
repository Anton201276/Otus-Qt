#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "enums.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Slot_DisplayNumber(const QString& disnum);
    void Slot_DisplayMemory(const QChar dismem);
    void Slot_DisplayFormula(const QString& disform);

signals:
   void Signal_PressDigitalButton(QChar dig);
   void Signal_PressControlButton(ControlKey cntl);
   void Signal_PressOperetionButton(Operation oper);


private slots:
    void on_click_controll();
    void on_click_digit();
    void on_click_operation();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
