#ifndef LOCALITY_H
#define LOCALITY_H

#include <QDialog>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "database.h"

namespace Ui {
class Locality;
}

class Locality : public QDialog
{
    Q_OBJECT

public:
    explicit Locality(QWidget *parent = nullptr);
    ~Locality();
public slots:
    void locality_opened();
private slots:
    void on_insert_clicked();

    void on_Delete_clicked();

private:
    Ui::Locality *ui;
    QSqlTableModel *model;
};

#endif // LOCALITY_H
