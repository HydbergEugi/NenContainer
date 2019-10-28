#ifndef AGREEMENT_ACCEPT_H
#define AGREEMENT_ACCEPT_H

#include <QDialog>

namespace Ui {
class agreement_accept;
}

class agreement_accept : public QDialog
{
    Q_OBJECT

public:
    explicit agreement_accept(QWidget *parent = nullptr);
    ~agreement_accept();
    QString name;
    QString surname;
    QString patronymic;
    QString unitId;
    QString first_cost;
    QString bargain;
    QString cost;
    QString sale_date;
    QString end_bargain;

public slots:
    void start_form(QString Aname, QString Asurname, QString Apatronymic,  QString AunitId,
                    QString Acost, QString Afirst_cost, QString Abargain, QString Asale_date,
                    QString Aend_bargain);
private slots:
    void on_pushButton_clicked();

signals:
    void accept_agreement();
private:
    Ui::agreement_accept *ui;
};

#endif // AGREEMENT_ACCEPT_H
