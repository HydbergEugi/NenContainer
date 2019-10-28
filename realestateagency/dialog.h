#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "database.h"
#include "agreement_accept.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void fillComboBox();
    void setHeaders();

private slots:
    void on_pushButton_clicked();

    void on_Delete_clicked();

    void on_AddAgreement_clicked();

    void real_estate_opened();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void accept_agreement1();

signals:
    void rowDeleted();
    void open_agreement_accept(QString Aname, QString Asurname, QString Apatronymic,  QString AunitId,
                               QString Acost, QString Afirst_cost, QString Abargain, QString Asale_date,
                               QString Aend_bargain);

private:
    QSqlQuery query;
    QSqlTableModel *model;
    Ui::Dialog *ui;


};

#endif // DIALOG_H
