#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QObject>
#include <QWidget>
#include <QProgressBar>
#include <QtMath>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

class RoundProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit RoundProgressBar(QWidget *parent = nullptr) {
        this->setFixedSize(square_size_, square_size_);
        scale_size_ = int(square_size_ * 0.65);

        background_circle_.setY(bount_width_);
        background_circle_.setX(bount_width_);
        background_circle_.setWidth(square_size_ - 2 * bount_width_);
        background_circle_.setHeight(square_size_ - 2 * bount_width_);


        center_square_point_.setX(square_size_/2);
        center_square_point_.setY(square_size_/2);
        QPoint left_p{square_size_ / 2 - scale_size_ / 2, square_size_ / 2 - scale_size_ / 2};
        progress_bar_circle_ = QRect(left_p, QSize(scale_size_, scale_size_));

        this->setMinimum(0);
        this->setMaximum(250);
        this->setValue(this->minimum());
        this->setEnabled(false);
    }

    void setTextUnitsMeasure(QString um) {
        units_measure_ = um;
    }

signals:

private:
    int square_size_ = 260;
    int bount_width_ = 3;
    int scale_size_;
    QPoint center_square_point_;
    QRect progress_bar_circle_;
    QRect background_circle_;
    QString units_measure_{"- km/h -"};

protected:
    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        painter.setBrush(QBrush(QColor(90,90,90), Qt::SolidPattern));
        painter.setPen(QPen(QColor(30,30,30), 4, Qt::SolidLine));
        painter.drawEllipse(background_circle_);

        if (!this->isEnabled()) {
            return;
        }

        //Рисуем главную дугу шкалы
        painter.setPen(QPen(QColor(200,200,200), 10, Qt::SolidLine));
        int startAngle = -45 * 16;
        int spanAngle = 270 * 16;
        painter.drawArc(progress_bar_circle_, startAngle, spanAngle);

        // Рисуем изменяющуюся дугу -135 * 16
        painter.setPen(QPen(QColor(20,140,250), 5, Qt::SolidLine));
        const float kp = 270.0 / this->maximum();
        float angle_duga = -16 * (kp * this->value());
        painter.drawArc(progress_bar_circle_, -135 * 16, angle_duga);

        painter.setPen(QPen(QColor(200,200,200), 3, Qt::SolidLine));
        const float shift_rad = 4;
        const float shift_text = 25;
        const float radius = shift_rad + scale_size_ / 2;
        const float radius_text = shift_text + scale_size_ / 2;
        const float len_scale = 10;
        float angle_scale = 45.0;
        QFont scale_font("Arial", 11, QFont::Bold, true);
        painter.setFont(scale_font);
        int num = (this->maximum() - this->minimum()) / 10;
        int k=0;
        while (angle_scale >= -225) {
            float radian_angle = qDegreesToRadians(angle_scale);
            float cosAngl = qCos(radian_angle);
            float sinAngl = qSin(radian_angle);
            QPointF p1(center_square_point_.x() - radius * cosAngl, center_square_point_.y() + radius * sinAngl);
            QPointF p2(center_square_point_.x() - (radius + len_scale) * cosAngl, center_square_point_.y() + (radius + len_scale) * sinAngl);
            painter.drawLine(p1, p2);
            QPointF text_center(center_square_point_.x() - radius_text * cosAngl, center_square_point_.y() + radius_text * sinAngl);
            QRect text_rec = QRect(text_center.x() - 20, text_center.y() - 7, 40, 14);
            painter.drawText(text_rec, Qt::AlignCenter, QString::number(num * k));
            k++;
            angle_scale -= 27;
        }

        QRect value_rect{center_square_point_.x() - 50, square_size_ - 80, 100, 60};
        QFont value_font("Arial", 28, QFont::Bold, true);
        painter.setFont(value_font);
        painter.drawText(value_rect, Qt::AlignCenter, QString::number(this->value()));
        value_rect.setY(square_size_ - 160);
        value_font.setPointSize(18);
        painter.setFont(value_font);
        painter.drawText(value_rect, Qt::AlignCenter, units_measure_);

        //Рисуем стрелку
        painter.save();
        painter.setBrush(QBrush(QColor(20,140,250), Qt::SolidPattern));
        painter.setPen(QPen(QColor(200,200,200), 2, Qt::SolidLine));
        QPolygon poly_arrow;
        QRect circle_arrow{QPoint(center_square_point_.x() - 10, center_square_point_.y() - 10), QSize(20,20)};
        painter.drawEllipse(circle_arrow);

        painter.translate(center_square_point_);
        poly_arrow << QPoint(-5, 0) << QPoint(-2, -(scale_size_/2 + bount_width_));
        poly_arrow << QPoint(2, -(scale_size_/2 + bount_width_)) << QPoint(5, 0);
        painter.rotate(-135.0 + kp * this->value());
        painter.drawPolygon(poly_arrow);
        painter.restore();

    }
};

#endif // ROUNDPROGRESSBAR_H
