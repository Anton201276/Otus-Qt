#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H

#include <QWidget>
#include <QAbstractButton>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QFont>

class RoundButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit RoundButton(QWidget *parent = nullptr) {
        setFixedSize(120, 80);
    }

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Фон (круг)
        int wightbound = 2;

        QRect button_rec(rect().x() + wightbound, rect().y() + wightbound, rect().width() - 2*wightbound, rect().height() - 2*wightbound);

        painter.setBrush(isDown() ? QColor(100,100,100) : QColor(150,150,150));
        painter.setPen(QPen(QColor(10,10,10), wightbound, Qt::SolidLine));
        painter.drawRoundedRect(button_rec,20,20);  // Рисуем эллипс на всю область

        // Текст
        QFont font = QFont("Arial", 12, QFont::Bold, true);
        painter.setPen(isDown() ? QColor(255,127,0) : QColor(127,255,127));
        painter.setFont(font);
        painter.drawText(rect(), Qt::AlignCenter, text());
    }
};
#endif // ROUNDBUTTON_H
