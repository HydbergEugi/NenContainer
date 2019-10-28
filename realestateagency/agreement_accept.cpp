#include "agreement_accept.h"
#include "ui_agreement_accept.h"
#include <QDebug>

agreement_accept::agreement_accept(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::agreement_accept)
{
    ui->setupUi(this);
}

agreement_accept::~agreement_accept()
{
    delete ui;


}

void agreement_accept::start_form(QString Aname, QString Asurname, QString Apatronymic,  QString AunitId,
                                  QString Acost, QString Afirst_cost, QString Abargain, QString Asale_date,
                                  QString Aend_bargain)
{
    ui->surname->setText(Asurname);
    ui->name->setText(Aname);
    ui->patronymic->setText(Apatronymic);
    ui->unitId->setText(AunitId);
    ui->first_cost->setText(Afirst_cost);
    ui->bargain->setText(Abargain);
    ui->cost->setText(Acost);
    ui->sale_date->setText(Asale_date);
    ui->end_bargain->setText(Aend_bargain);

    show();
}

void agreement_accept::on_pushButton_clicked()
{
    emit accept_agreement();
    hide();
}
