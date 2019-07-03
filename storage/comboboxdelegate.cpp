#include "comboboxdelegate.h"

#include <QtWidgets>
#include "ComboBoxDelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent):QItemDelegate(parent)
{
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &,const QModelIndex &) const
{
    QDateTimeEdit *editor = new QDateTimeEdit(parent);
    editor->setDisplayFormat("yyyy/d/M");
    editor->setCalendarPopup(true);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
    if (dateEditor)
    {
        dateEditor->setDate(QDate::fromString(index.model()->data(index, Qt::EditRole).toString(), "yyyy/d/M"));
    }
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
    if (dateEditor)
    {
        model->setData(index, dateEditor->date().toString("yyyy/d/M"));
    }
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
