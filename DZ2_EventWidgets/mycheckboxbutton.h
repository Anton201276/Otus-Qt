#ifndef MYCHECKBOXBUTTON_H
#define MYCHECKBOXBUTTON_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QString>

class MyCheckBoxButton : public QCheckBox
{
    Q_OBJECT
public:
    explicit MyCheckBoxButton(QWidget *parent = nullptr) {
        this->setTristate(true);
        this->setFixedSize(switch_size_, switch_size_);
        center_point_.setX(switch_size_/2);
        center_point_.setY(switch_size_/2);

        central_circle_.setX(center_point_.x() - switch_size_/2 + border_);
        central_circle_.setY(center_point_.y() - switch_size_/2 + border_);
        central_circle_.setWidth(switch_size_ - 2 * border_ - width_);
        central_circle_.setHeight(switch_size_ - 2 * border_ - width_);

        text_circle_.setX(center_point_.x() - 30);
        text_circle_.setY(center_point_.y() - 20);
        text_circle_.setWidth(60);
        text_circle_.setHeight(40);
    }

signals:

private:
    int switch_size_ = 120;
    int border_ = 10;
    int width_ = 5;
    QPoint center_point_;
    QRect central_circle_;
    QRect text_circle_;
    const QColor color_off_ = QColor("#FFF61F");
    const QColor color_on_ = QColor("#55FA3E");
    const QColor color_engine_ = QColor("#2540D9");

    const QString txt_off_{"Вкл"};
    const QString txt_on_{"Старт"};
    const QString txt_eng_{"Откл"};


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        QString txt;
        QColor color;
        painter.setRenderHint(QPainter::Antialiasing, true);

        QRadialGradient gradient(center_point_,switch_size_ / 2 - border_);
        painter.setBrush(gradient);
        painter.setBrush(QColor(140,140,140));

        switch (this->checkState()) {
            case Qt::Unchecked:
                txt = txt_off_;
                color = color_off_;
                break;
            case Qt::PartiallyChecked:
                txt = txt_on_;
                color = color_on_;
                break;
            case Qt::Checked:
                txt = txt_eng_;
                color = color_engine_;
                break;
        }

        // Текст
        QFont font = QFont("Arial", 12, QFont::Bold, true);
        painter.setPen(QPen(color, border_, Qt::SolidLine));
        painter.setFont(font);
        painter.drawEllipse(central_circle_);
        painter.drawText(text_circle_, Qt::AlignCenter,txt);

    }

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event){
        if (event->buttons() & Qt::LeftButton) {
            switch (this->checkState()) {
                case Qt::Unchecked: this->setCheckState(Qt::PartiallyChecked); break;
                case Qt::PartiallyChecked: this->setCheckState(Qt::Checked); break;
                case Qt::Checked: this->setCheckState(Qt::Unchecked); break;
            }
            update();
        }
    }
};

#endif // MYCHECKBOXBUTTON_H

