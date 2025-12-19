//#pragma once
#include <string>
#include <sstream>
#include <optional>
#include <functional>
#include <QDebug>
#include <QString>
#include "calculator.h"
#include "mainwindow.h"
#include "enums.h"

class Controller : public QObject {
    Q_OBJECT
public:
    Controller(){}

signals:
    void Signal_DisplayNumber(const QString& disnum);
    void Signal_DisplayMemory(const QChar dismem);
    void Signal_DisplayFormula(const QString& disform);

public slots:

    void Slot_ReciveDigitButton(QChar dig) {
        if (next_exp_) {
            display_number_ = "";
            next_exp_ = false;
        }
        display_number_ += dig;
        if (display_number_.length() < 17) {
            emit Signal_DisplayNumber(display_number_);
        }
        else {
            emit Signal_DisplayNumber("error");
        }
    }

    void Slot_ReciveControllButton(ControlKey cntl) {
        switch (cntl) {
            case ControlKey::CLEAR:
                reset_calculator();
                emit Signal_DisplayNumber("0");
                emit Signal_DisplayFormula(display_formula_);

                break;

            case ControlKey::EQUALS:
                if (!calc_action_) return;
                else {
                    display_formula_ +=  display_number_ + "=";
                    double num = display_number_.toDouble();
                    std::optional<Error> result = calc_action_(num);
                    if (result.has_value()) {
                        reset_calculator();
                        display_number_ = "Error";
                    }
                    else {
                        display_number_.clear();
                        display_number_ = QString::number(calculator_.GetNumber());
                        calc_action_ = nullptr;
                    }
                    emit Signal_DisplayNumber(display_number_);
                    emit Signal_DisplayFormula(display_formula_);
                }
                break;

            case ControlKey::MEM_LOAD:

                if (calc_action_ == nullptr) {
                    calculator_.Load();
                    display_number_ = QString::number(calculator_.GetNumber());
                }
                else {
                    std::optional<double> mem = calculator_.GetMemoryNumber();
                    display_number_ = QString::number(mem.value_or(0));
                }

                emit Signal_DisplayNumber(display_number_);
                break;

            case ControlKey::BACKSPACE:
                if (display_number_.length() > 1) {
                    display_number_ = display_number_.mid(0, display_number_.size() - 1);
                }
                else {
                    display_number_ = "0";
                }
                emit Signal_DisplayNumber(display_number_);
                break;

            case ControlKey::DOT_KEY:
                if (display_number_.length() == 0 || display_number_ == "0") {
                    display_number_ = "0.";
                }
                else if (display_number_.lastIndexOf('.') < 0){
                    display_number_ += ".";
                }
                emit Signal_DisplayNumber(display_number_);
                break;

            case ControlKey::MEM_CLEAR:
                calculator_.ResetMemoryNumber();
                emit Signal_DisplayMemory(' ');
                break;

            case ControlKey::PLUS_MINUS:
                if (display_number_[0] != '-') {
                    display_number_ = "-" + display_number_;
                }
                else {
                    display_number_ = display_number_.mid(1, display_number_.size() - 1);
                }
                emit Signal_DisplayNumber(display_number_);
                break;

            case ControlKey::MEM_SAVE:
                if (!display_number_.isNull() && display_number_ != "0") {
                    calculator_.Set(display_number_.toDouble());
                    calculator_.Save();
                    emit Signal_DisplayMemory('M');
                }
                break;
        }
    }

    void Slot_ReciveOperetionButton(Operation oper) {
        switch (oper) {
            case Operation::POWER:
                calc_operation('^');
                calc_action_ = [this](double num) {return calculator_.Pow(num);};

                emit Signal_DisplayNumber(display_number_);
                emit Signal_DisplayFormula(display_formula_);

                break;

            case Operation::ADDITION:
                calc_operation('+');
                calc_action_ = [this](double num) {return calculator_.Add(num);};

                emit Signal_DisplayNumber(display_number_);
                emit Signal_DisplayFormula(display_formula_);
                break;

            case Operation::DIVISION:
                calc_operation('/');
                calc_action_ = [this](double num) {return calculator_.Div(num);};

                emit Signal_DisplayNumber(display_number_);
                emit Signal_DisplayFormula(display_formula_);
                break;

            case Operation::SUBTRACTION:
                calc_operation('-');
                calc_action_ = [this](double num) {return calculator_.Sub(num);};

                emit Signal_DisplayNumber(display_number_);
                emit Signal_DisplayFormula(display_formula_);

                break;

            case Operation::MULTIPLICATION:
                calc_operation('*');
                calc_action_ = [this](double num) {return calculator_.Mul(num);};

                emit Signal_DisplayNumber(display_number_);
                emit Signal_DisplayFormula(display_formula_);
                break;
        }
    }


private:
    void reset_calculator() {
        calc_operation_ = "";
        calculator_.Set(0);
        display_number_.clear();
        display_formula_.clear();
        calc_action_ = nullptr;
        next_exp_ = false;
    }

    bool calc_operation(QChar sign) {
        if (calc_action_) {
            double num = display_number_.toDouble();
            std::optional<Error> result = calc_action_(num);
            if (result.has_value()) {
                reset_calculator();
                display_number_ = "Error";
                return false;
            }
            else {
                display_number_ = QString::number(calculator_.GetNumber());
                display_formula_ = display_number_ + sign;
                next_exp_ = true;
            }
        }
        else {
            if (display_number_.isNull()) {
                display_number_ = "0";
            }
            calculator_.Set(display_number_.toDouble());
            display_formula_ = display_number_ + sign;
            next_exp_ = true;
        }
        return true;
    }


private:
    std::function<std::optional<Error>(double)> calc_action_;
    QString calc_operation_{};
    bool next_exp_ = false;
    QString display_number_{};
    QString display_formula_{};
    Calculator calculator_;
};
