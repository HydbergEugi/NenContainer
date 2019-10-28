// Используемые переменные:
// user - информация о текущем пользователе.
//
// Используемые функции:
// Dialog(QWidget *parent) - инициализация формы;
// ~Dialog() - удаление формы;
// on_pushButton_clicked() - кнопка добавления записи;
// on_Delete_clicked() - кнопка удаления записи;
// on_AddAgreement_clicked() - кнопка добавления договора;
// real_estate_opened() - слот открытия формы;
// fillComboBox() - заполнение выпадающего списка;
// on_pushButton_2_clicked() - кнопка заполнения выпадающего списка;
// on_pushButton_3_clicked() - кнопка установки фильтров;
// setHeaders() - установление заголовков столбцов.

#include "dialog.h"
#include "ui_dialog.h"
#include <QItemDelegate>
#include <QComboBox>
#include <QStyledItemDelegate>
#include "comboboxitemdelegate.h"
#include "database.h"
#include "users.h"
#include "autorization.h"
#include "agreement_accept.h"
#include <QMessageBox>

//agreement_accept example;
extern currentUser user;

// /////////////////////////////////////////////////////////////////////////////////////////
// Dialog(QWidget *parent) - инициализация формы.
//
// Формальные параметры:
// *parent - ссылка на родительское окно.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы;
// /////////////////////////////////////////////////////////////////////////////////////////
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    fillComboBox();
    setWindowTitle("Просмотр недвижимости");

    model = new QSqlTableModel;
    model->setTable("Real_estate_unit");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, "Номер объекта");
    model->setHeaderData(1, Qt::Horizontal, "Тип жилья");
    model->setHeaderData(2, Qt::Horizontal, "Тип дома");
    model->setHeaderData(3, Qt::Horizontal, "Местоположение");
    model->setHeaderData(4, Qt::Horizontal, "Тип отделки");
    model->setHeaderData(5, Qt::Horizontal, "Тип окон");
    model->setHeaderData(6, Qt::Horizontal, "Напольное \n покрытие");
    model->setHeaderData(7, Qt::Horizontal, "Тип потолка");
    model->setHeaderData(8, Qt::Horizontal, "Этаж");
    model->setHeaderData(9, Qt::Horizontal, "Стоимость");
    model->setHeaderData(10, Qt::Horizontal, "Скидка %");
    model->setHeaderData(11, Qt::Horizontal, "Дата окончания \n скидки");
    model->setHeaderData(12, Qt::Horizontal, "Площадь");
    ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate();
    ui->tableView->setItemDelegateForColumn(3,cbid);
    ui->tableView->setItemDelegateForColumn(6,cbid);
    ui->tableView->setModel(model);



}
// /////////////////////////////////////////////////////////////////////////////////////////
// ~Dialog() - удаление формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
Dialog::~Dialog()
{
    delete ui;
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_pushButton_clicked() - кнопка добавление новой записи.
//
// Локальные переменные:
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::on_pushButton_clicked()
{

    model->insertRows(model->rowCount(),1);
}

// /////////////////////////////////////////////////////////////////////////////////////////
// on_Delete_clicked() - кнопка удаления записи.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::on_Delete_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
    model->select();
}

// /////////////////////////////////////////////////////////////////////////////////////////
// on_AddAgreement_clicked() - кнопка добавления договора.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы;
// purchQuery - запрос для договора;
// unitQuery - запрос для объекта недвижимости;
// unitRec - запись результата запроса по недвижимости;
// insertAgreement - строка запроса;
// purchId - id договора;
// custId - id покупателя;
// unitId - id объекта недвижимости;
// cost - стоимость;
// saleDate - дата покупки;
// endBargain - дата окончания скидки.
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::on_AddAgreement_clicked()
{
    QSqlQuery purchQuery;
    QSqlQuery unitQuery;
    QSqlQuery custQuery;
    QSqlQuery dateQuery;
    dateQuery.exec("SELECT * FROM currentdate");
    dateQuery.seek(0);
    QSqlRecord dateRec = dateQuery.record();
    custQuery.exec("SELECT name, surname, patronymic FROM customer");
    custQuery.seek(user.getUserName());
    QSqlRecord custRec = custQuery.record();
    unitQuery.exec("SELECT * FROM Real_estate_unit");
    unitQuery.seek(ui->tableView->currentIndex().row());
    QSqlRecord unitRec = unitQuery.record();
    QString insertAgreement = "INSERT INTO purchase_agreement "
                              "VALUES(%1, %2, %3, %4, %5, '%6');";

    purchQuery.exec("Select purchId From purchase_agreement");
    QSqlRecord purchRec = purchQuery.record();
    purchQuery.last();
    int purchId = purchQuery.value(purchRec.indexOf("purchId")).toInt();
    int custId = user.getUserName();
    int unitId = unitQuery.value(unitRec.indexOf("unitId")).toInt();
    float cost = unitQuery.value(unitRec.indexOf("cost")).toFloat();
    cost -= cost*unitQuery.value(unitRec.indexOf("bargain")).toFloat()/100;
    QString saleDate = unitQuery.value(unitRec.indexOf("sale_date")).toString();
    QString endBargain = unitQuery.value(unitRec.indexOf("end_bargain")).toString();
    insertAgreement = insertAgreement.arg(purchId+1).arg(custId).arg(unitId).arg(cost).arg("getdate()").arg(endBargain);


    QString Aname = custQuery.value(custRec.indexOf("name")).toString();
    qDebug() << custQuery.value(custRec.indexOf("name")).toString();
    QString Asurname = custQuery.value(custRec.indexOf("surname")).toString();
    QString Apatronymic = custQuery.value(custRec.indexOf("patronymic")).toString();
    QString AunitId =  unitQuery.value(unitRec.indexOf("unitId")).toString();
    float Acost = unitQuery.value(unitRec.indexOf("cost")).toFloat() -
            unitQuery.value(unitRec.indexOf("cost")).toFloat()*
            unitQuery.value(unitRec.indexOf("bargain")).toFloat()/100;
    QString Afirst_cost = unitQuery.value(unitRec.indexOf("cost")).toString();
    QString Abargain = unitQuery.value(unitRec.indexOf("bargain")).toString();
    QString Asale_date = dateQuery.value(dateRec.indexOf("now_date")).toString();
    QString Aend_bargain = unitQuery.value(unitRec.indexOf("end_bargain")).toString();
    emit open_agreement_accept( Aname,  Asurname,  Apatronymic,   AunitId,
                                QString::number(Acost),  Afirst_cost,  Abargain,  Asale_date,
                                Aend_bargain);


}
// /////////////////////////////////////////////////////////////////////////////////////////
// real_estate_opened() - слот открытия формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::real_estate_opened()
{
    if(user.getUserName()!=0)
    {
        ui->pushButton->hide();
        ui->Delete->hide();
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    show();
}
// /////////////////////////////////////////////////////////////////////////////////////////
// fillComboBox() - заполнение выпадающего списка.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// rec - запись запроса;
// query - запрос;
// values - значения для выпадающего списка.
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::fillComboBox()
{
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    QSqlRecord rec;
    QSqlQuery query;
    query.exec("SELECT value FROM floor_covering");
    rec = query.record();
    QString values;

    while(query.next())
    {
        values = query.value(rec.indexOf("value")).toString();
        values = deleteGaps(values);
       ui->comboBox->addItem(values);
    }

    query.exec("SELECT value FROM locality");
    rec = query.record();

    while(query.next())
    {
        values = query.value(rec.indexOf("value")).toString();
        values = deleteGaps(values);
       ui->comboBox_2->addItem(values);
    }
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_pushButton_2_clicked() - кнопка заполнения выпадающего списка.
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::on_pushButton_2_clicked()
{
    fillComboBox();
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_pushButton_3_clicked() - кнопка установки фильтров.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::on_pushButton_3_clicked()
{
    if ((ui->comboBox->currentText() != "")&& (ui->comboBox_2->currentText() != ""))
        model->setFilter("unitId in (SELECT unitId FROM Real_estate_unit WHERE locality = '"+ui->comboBox_2->currentText()+"'"
                         " and floor_covering = '"+ui->comboBox->currentText()+"')");
    if ((ui->comboBox->currentText() != "")&& (ui->comboBox_2->currentText() == ""))
        model->setFilter("unitId in (SELECT unitId FROM Real_estate_unit WHERE floor_covering = '"+ui->comboBox->currentText()+"')");
    if ((ui->comboBox->currentText() == "")&& (ui->comboBox_2->currentText() != ""))
        model->setFilter("unitId in (SELECT unitId FROM Real_estate_unit WHERE locality = '"+ui->comboBox_2->currentText()+"')");
    if ((ui->comboBox->currentText() == "")&& (ui->comboBox_2->currentText() == ""))
        model->setTable("Real_estate_unit");
    model->select();
    setHeaders();
}
// /////////////////////////////////////////////////////////////////////////////////////////
// setHeaders() - установление заголовков столбцов.
//
// Локальные переменные:
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Dialog::setHeaders()
{
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, "Номер объекта");
    model->setHeaderData(1, Qt::Horizontal, "Тип жилья");
    model->setHeaderData(2, Qt::Horizontal, "Тип дома");
    model->setHeaderData(3, Qt::Horizontal, "Местоположение");
    model->setHeaderData(4, Qt::Horizontal, "Тип отделки");
    model->setHeaderData(5, Qt::Horizontal, "Тип окон");
    model->setHeaderData(6, Qt::Horizontal, "Напольное \n покрытие");
    model->setHeaderData(7, Qt::Horizontal, "Тип потолка");
    model->setHeaderData(8, Qt::Horizontal, "Этаж");
    model->setHeaderData(9, Qt::Horizontal, "Стоимость");
    model->setHeaderData(10, Qt::Horizontal, "Скидка %");
    model->setHeaderData(11, Qt::Horizontal, "Дата окончания \n скидки");
    model->setHeaderData(12, Qt::Horizontal, "Площадь");
}

void Dialog::accept_agreement1()
{
    QSqlQuery purchQuery;
    QSqlQuery unitQuery;
    QSqlQuery custQuery;

    custQuery.exec("SELECT name, surname, patronymic FROM customer");
    custQuery.seek(user.getUserName());
    QSqlRecord custRec = custQuery.record();
    unitQuery.exec("SELECT * FROM Real_estate_unit");
    unitQuery.seek(ui->tableView->currentIndex().row());
    QSqlRecord unitRec = unitQuery.record();
    QString insertAgreement = "INSERT INTO purchase_agreement "
                              "VALUES(%1, %2, %3, %4, %5, '%6');";

    purchQuery.exec("Select purchId From purchase_agreement");
    QSqlRecord purchRec = purchQuery.record();
    purchQuery.last();
    int purchId = purchQuery.value(purchRec.indexOf("purchId")).toInt();
    int custId = user.getUserName();
    int unitId = unitQuery.value(unitRec.indexOf("unitId")).toInt();
    float cost = unitQuery.value(unitRec.indexOf("cost")).toFloat();
    cost -= cost*unitQuery.value(unitRec.indexOf("bargain")).toFloat()/100;
    QString saleDate = unitQuery.value(unitRec.indexOf("sale_date")).toString();
    QString endBargain = unitQuery.value(unitRec.indexOf("end_bargain")).toString();
    insertAgreement = insertAgreement.arg(purchId+1).arg(custId).arg(unitId).arg(cost).arg("getdate()").arg(endBargain);

    if (!query.exec(insertAgreement))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить договор");
    }
    else
    {
        QMessageBox::information(this, "Информация", "Договор успешно добавлен");
    }
}
