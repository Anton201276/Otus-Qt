#ifndef MYWHEELSELECTOR_H
#define MYWHEELSELECTOR_H

#include <QWidget>
#include <QSlider>
#include <QLayout>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

class MyWheelSelector : public QSlider
{
    enum MouseArmState {
        ArmOff,
        ArmOn,
        ArmMoving
    };
    Q_OBJECT
public:
    explicit MyWheelSelector(QWidget *parent = nullptr) {
        this->setFixedSize(90, 180);
        this->setOrientation(Qt::Vertical);
        this->setMinimum(-1);
        this->setMaximum(4);
        this->setValue(0);
        this->setMouseTracking(true);

        arm_rectangle_.setX(arm_left_);
        arm_rectangle_.setY(ArmRectagleGetY(this->value()));
        arm_rectangle_.setWidth(radius_ * 3);
        arm_rectangle_.setHeight(radius_);
    }

//signals:

private:
    QString GetWheelSign(int whl) {
        QString whls{};
        switch (whl) {
            case -1: whls = "R";
                break;
            case 0: whls = "N";
                break;
            case 1: whls = "D1";
                break;
            case 2: whls = "D2";
                break;
            case 3: whls = "D3";
                break;
            case 4: whls = "D4";
                break;
        }
        return whls;
    }

    int ArmRectagleGetY(int whl) {
        return arm_y_down_ - (whl + 1) * arm_y_offset_;
    }

private:
    bool selecting_wheel_ = false;
    const int wight_bound_ = 2;
    const int wight_line_selector_ = 6;
    const int vertical_offset_ = 10;
    const int radius_ = 12;
    const int dist_ = 3;
    const int arm_left_ = dist_ * 3;
    const int arm_y_down_ = (2 * radius_ + dist_) * 5 + vertical_offset_ + radius_ / 2;
    const int arm_y_offset_ = 2 * radius_ + dist_;
    QRect arm_rectangle_;
    MouseArmState arm_state_ = ArmOff;
    QPoint arm_grab_point;
    int next_value_;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event){

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QRect track_bar(rect().x() + wight_bound_, rect().y() + wight_bound_, rect().width() - 2*wight_bound_, rect().height() - 2*wight_bound_);

        painter.setPen(QPen(QColor(10,10,10), 2, Qt::SolidLine));
        painter.drawRoundedRect(track_bar,10,10);
        track_bar.setX(rect().width()/4 - wight_line_selector_/2);
        track_bar.setY(vertical_offset_);
        track_bar.setWidth(vertical_offset_);
        track_bar.setHeight(rect().height() - 2 * vertical_offset_);
        painter.drawRoundedRect(track_bar,2,2);

        //Рисуем передачи
        QFont font = QFont("Arial", 9, QFont::Bold, true);
        QPoint point_wheel(rect().width()*3/4 - radius_, vertical_offset_ + 5 * (2 * radius_ + dist_));
        painter.setFont(font);
        painter.setPen(QPen(QColor(100,100,100), 2, Qt::SolidLine));
        painter.setBrush(QColor(200,200,200));
        track_bar.setX(point_wheel.x());
        track_bar.setY(point_wheel.y());
        track_bar.setWidth(radius_ * 2);
        track_bar.setHeight(radius_ * 2);
        bool need_restore = false;
        for (int i = -1; i < 5; i++) {
            if (this->value() == i && arm_state_ != MouseArmState::ArmMoving) {
                painter.save();
                painter.setPen(QPen(QColor(255,255,50), 2, Qt::SolidLine));
                painter.setBrush(QColor(0,200,100));
                need_restore = true;
            }

            painter.drawEllipse(track_bar);
            painter.drawText(track_bar, Qt::AlignCenter, GetWheelSign(i));
            point_wheel.ry() -= 2 * radius_ + dist_;
            track_bar.setY(point_wheel.y());
            track_bar.setHeight(radius_ * 2);

            if (need_restore) {
                need_restore = false;
                painter.restore();
            }
        }

        //Рисуем переключатель
        if (arm_state_ == MouseArmState::ArmOff) {
            painter.save();
            painter.setPen(QPen(QColor(255,255,50), 2, Qt::SolidLine));
            painter.setBrush(QColor(0,200,100));
            painter.drawRoundedRect(arm_rectangle_,3,3);
            painter.restore();

        }
        else if (arm_state_ == MouseArmState::ArmOn) {
            painter.save();
            painter.setPen(QPen(QColor(0,0,0), 2, Qt::SolidLine));
            painter.setBrush(QColor(100,100,100));
            painter.drawRoundedRect(arm_rectangle_,3,3);
            painter.restore();
        }
        else if (arm_state_ == MouseArmState::ArmMoving) {
            painter.save();
            painter.setPen(QPen(QColor(0,0,0), 2, Qt::SolidLine));
            painter.setBrush(QColor(200,200,200));
            painter.drawRoundedRect(arm_rectangle_,3,3);
            painter.restore();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) {
        if (arm_state_ == MouseArmState::ArmOff && arm_rectangle_.contains(event->pos())) {
            arm_state_ = MouseArmState::ArmOn;
        }
        else if (arm_state_ == MouseArmState::ArmOn && !arm_rectangle_.contains(event->pos())){
            arm_state_ = MouseArmState::ArmOff;
        }
        else if (arm_state_ == MouseArmState::ArmMoving) {
            QPoint delta_point = arm_grab_point - event->pos();
            if (delta_point.y() > (radius_ + dist_) && next_value_ < this->maximum()) {
                next_value_++;
                arm_rectangle_.setY(ArmRectagleGetY(next_value_));
                arm_rectangle_.setWidth(radius_ * 3);
                arm_rectangle_.setHeight(radius_);
                arm_grab_point.setX(arm_rectangle_.x());
                arm_grab_point.setY(arm_rectangle_.y());
            }
            else if (delta_point.y() < -(radius_ + dist_) && next_value_ > this->minimum()) {
                next_value_--;
                arm_rectangle_.setY(ArmRectagleGetY(next_value_));
                arm_rectangle_.setWidth(radius_ * 3);
                arm_rectangle_.setHeight(radius_);
                arm_grab_point.setX(arm_rectangle_.x());
                arm_grab_point.setY(arm_rectangle_.y());
            }
        }
        update();
    }
    void mousePressEvent(QMouseEvent *event) {
        if ((event->buttons() & Qt::LeftButton)
            && (arm_state_ == MouseArmState::ArmOn
                || (arm_state_ == MouseArmState::ArmOff &&  arm_rectangle_.contains(event->pos())))) {
             arm_state_ = MouseArmState::ArmMoving;
             arm_grab_point = event->pos();
             next_value_ = this->value();
        }
        update();
    }
    void mouseReleaseEvent(QMouseEvent *event) {
        arm_state_ = MouseArmState::ArmOff;
        this->setValue(next_value_);
        update();
    }
};

#endif // MYWHEELSELECTOR_H
