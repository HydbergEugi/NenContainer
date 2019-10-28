#ifndef FLOOR_COVERING_H
#define FLOOR_COVERING_H

#include <QDialog>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "database.h"

namespace Ui {
class floor_covering;
}

class floor_covering : public QDialog
{
    Q_OBJECT

public:
    explicit floor_covering(QWidget *parent = nullptr);
    ~floor_covering();

private slots:
    void on_insert_clicked();

    void on_delete_2_clicked();

    void floor_covering_opened();

private:
    Ui::floor_covering *ui;
    QSqlTableModel *model;
};

#endif // FLOOR_COVERING_H
