#include "comboboxitemdelegate.h"
#include <QComboBox>
#include "database.h"

ComboBoxItemDelegate::ComboBoxItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{ 
}


ComboBoxItemDelegate::~ComboBoxItemDelegate()
{
}


QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);

    if (index.column() == 6)
    {
        QSqlRecord rec;
        QSqlQuery query;

        query.exec("SELECT value FROM floor_covering");
        rec = query.record();
        QString values;

        while(query.next())
        {
            values = query.value(rec.indexOf("value")).toString();
            values.replace(" ", "");
            qDebug() <<  rec << " ";
            cb->addItem(values);
        }

    }
    else
    {
        QSqlRecord rec;
        QSqlQuery query;

        query.exec("SELECT value FROM locality");
        rec = query.record();
        QString values;

        while(query.next())
        {
            values = query.value(rec.indexOf("value")).toString();
            values = deleteGaps(values);
            cb->addItem(values);
        }
    }
    return cb;
}


void ComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cb->findText(currentText);
    if (cbIndex >= 0)
       cb->setCurrentIndex(cbIndex);

}


void ComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);

    model->setData(index, cb->currentText(), Qt::EditRole);

}
