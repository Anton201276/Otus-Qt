#ifndef SOKRATDBDELEGATE_H
#define SOKRATDBDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QSet>
#include <QPainter>
#include <QApplication>
#include "CommonDefineType.h"

//class EditUnabledAllCellDelegate : public QStyledItemDelegate
//{
//    Q_OBJECT
//public:
//    explicit EditUnabledAllCellDelegate(QObject *parent = nullptr)
//        : QStyledItemDelegate(parent) {}

//    QWidget* createEditor(QWidget *,
//                          const QStyleOptionViewItem &,
//                          const QModelIndex &) const override
//    {
//        return nullptr;
//    }
//};

//class ColumnRestrictedDelegate : public QStyledItemDelegate
//{
//    Q_OBJECT
//public:
//    explicit ColumnRestrictedDelegate(QObject *parent = nullptr)
//        : QStyledItemDelegate(parent) {}

//protected:
//    void paint(QPainter *painter,
//               const QStyleOptionViewItem &option,
//               const QModelIndex &index) const override
//    {
//        if (index.column() == 6) {
//            bool ok;
//            int value = index.data().toInt(&ok);
//            if (ok) {
//                QStyleOptionViewItem opt = option;
//                initStyleOption(&opt, index);
//                opt.text = QString("0x%1").arg(value, 0, 16);
//                QApplication::style()->drawControl(
//                    QStyle::CE_ItemViewItem, &opt, painter);
//                return;
//            }
//        }

//        QStyledItemDelegate::paint(painter, option, index);
//    }

//    QWidget* createEditor(QWidget *parent,
//                          const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const override
//    {
//        if (index.column() > 2 && index.column() < 6)
//            return QStyledItemDelegate::createEditor(parent, option, index);

//        return nullptr;
//    }
//};

class SmartTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
//    enum Mode {
//        ReadOnlyAll,        // запретить всё
//        EditColumns3to5     // разрешить только 3-5
//    };

    explicit SmartTableDelegate(DelegateMode mode,
                                QObject *parent = nullptr)
        : QStyledItemDelegate(parent),
          m_mode(mode)
    {}

protected:

    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        if (m_mode == ReadOnlyAll)
            return nullptr;

        if (m_mode == EditColumns3to5) {
            if (index.column() >= 3 && index.column() <= 5)
                return QStyledItemDelegate::createEditor(parent, option, index);

            return nullptr;
        }

        return nullptr;
    }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override {
        if (index.column() == 6 && m_mode == DelegateMode::EditColumns3to5) {
            bool ok;
            int value = index.data().toInt(&ok);
            if (ok) {
                QStyleOptionViewItem opt = option;
                initStyleOption(&opt, index);
                opt.text = QString("0x%1").arg(value, 4, 16, QChar('0'));
                QApplication::style()->drawControl(
                    QStyle::CE_ItemViewItem, &opt, painter);
                return;
            }
        }

        QStyledItemDelegate::paint(painter, option, index);
    }

private:
    DelegateMode m_mode;
};

#endif // SOKRATDBDELEGATE_H

/*
Qt::ItemFlags flags(const QModelIndex &index) const override
{
    Qt::ItemFlags f = QSqlTableModel::flags(index);

    if (mode == ReadOnlyAll)
        return f & ~Qt::ItemIsEditable;

    if (mode == EditColumns3to5) {
        if (index.column() < 3 || index.column() > 5)
            return f & ~Qt::ItemIsEditable;
    }

    return f;
}
 */
