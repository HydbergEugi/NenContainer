#ifndef PURCHASES_H
#define PURCHASES_H

#include <QDialog>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "database.h"

namespace Ui {
class Purchases;
}

class Purchases : public QDialog
{
    Q_OBJECT

public:
    explicit Purchases(QWidget *parent = nullptr);
    ~Purchases();
    void fillComboBox();
    void setHeaders();
private slots:

    void on_pushButton_clicked();
    void purchases_opened();

    void on_Delete_clicked();

    void on_pushButton_2_clicked();
signals:
    void purch_update();
private:
    Ui::Purchases *ui;
    QSqlTableModel *model;

};

#endif // PURCHASES_H
