#ifndef SOKRATDBDELEGATE_H
#define SOKRATDBDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QSet>
#include <QPainter>

class EditUnabledAllCellDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EditUnabledAllCellDelegate(QObject *parent = nullptr)
        :QStyledItemDelegate(parent) {}

    // Запрещаем создание редактора
    QWidget* createEditor(QWidget *parent,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override
    {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return nullptr;
    }

signals:
    void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    void commitData(QWidget *editor);
    void sizeHintChanged(const QModelIndex &index);
};

class ColumnRestrictedDelegate  : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ColumnRestrictedDelegate(QObject *parent = nullptr)
        :QStyledItemDelegate(parent) {}

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const override
        {

            if (!index.isValid()) {
                QStyledItemDelegate::paint(painter, option, index);
                return;
            }

            if (index.column() == 6) {
                bool ok;
                int value = index.data().toInt(&ok);
                if (ok) {
                    QString hexValue = QString("0x%1").arg(value, 0, 16);
                    painter->drawText(option.rect, Qt::AlignCenter, hexValue);
                } else {
                    QStyledItemDelegate::paint(painter, option, index);
                }
            }
            else {
                QStyledItemDelegate::paint(painter, option, index);
            }
        }

    QWidget* createEditor(QWidget *parent,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override
    {
        Q_UNUSED(option);
        Q_UNUSED(index);

        if (index.column() > 2 && index.column() < 6) {
            return QStyledItemDelegate::createEditor(parent, option, index);
        }

        return nullptr;
    }
signals:
    void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    void commitData(QWidget *editor);
    void sizeHintChanged(const QModelIndex &index);
};

#endif // SOKRATDBDELEGATE_H
