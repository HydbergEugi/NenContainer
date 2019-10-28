#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "database.h"

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_Submit_clicked();
    void start_registration();
private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
