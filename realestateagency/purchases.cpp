// Используемые переменные:
// user - информация о текущем пользователе.
//
// Используемые функции:
// Purchases(QWidget *parent) - инициализация формы;
// ~Purchases() - удаление формы;
// on_pushButton_clicked() - кнопка установки фильтров;
// purchases_opened() - слот открытия формы;
// on_Delete_clicked() - кнопка удаления записи;
// fillComboBox() - заполнение выпадающего списка;
// on_pushButton_2_clicked() - кнопка заполнения выпадающего списка;
// setHeaders() - установление заголовков столбцов.

#include "purchases.h"
#include "ui_purchases.h"
#include "database.h"
#include "users.h"

extern currentUser user;

// /////////////////////////////////////////////////////////////////////////////////////////
// Purchases(QWidget *parent) - инициализация формы.
//
// Формальные параметры:
// *parent - ссылка на родительское окно.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы;
// /////////////////////////////////////////////////////////////////////////////////////////
Purchases::Purchases(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Purchases)
{
    ui->setupUi(this);
    setWindowTitle("Просмотр договоров");

    fillComboBox();

    model = new QSqlTableModel;
    model->setTable("purchase_agreement");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, "Номер \n договора");
    model->setHeaderData(2, Qt::Horizontal, "Номер объекта");
    model->setHeaderData(3, Qt::Horizontal, "Итоговая \n cтоимость");
    model->setHeaderData(4, Qt::Horizontal, "Дата \n покупки");
    model->setHeaderData(5, Qt::Horizontal, "Дата \n окончания \n скидки");

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->hideColumn(1);

}
// /////////////////////////////////////////////////////////////////////////////////////////
// ~Purchases() - удаление формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
Purchases::~Purchases()
{
    delete ui;
}

// /////////////////////////////////////////////////////////////////////////////////////////
// on_pushButton_clicked() - кнопка установки фильтров.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Purchases::on_pushButton_clicked()
{
        QString str = "custId = '"+QString::number(user.getUserName())+"'";
        if ((ui->comboBox->currentText() != "")&& (ui->comboBox_2->currentText() != ""))
            model->setFilter("unitId in (SELECT unitId FROM Real_estate_unit WHERE locality = '"+ui->comboBox_2->currentText()+"'"
                             " and floor_covering = '"+ui->comboBox->currentText()+"') and "+str);
        if ((ui->comboBox->currentText() != "")&& (ui->comboBox_2->currentText() == ""))
            model->setFilter("unitId in (SELECT unitId FROM Real_estate_unit WHERE floor_covering = '"+ui->comboBox->currentText()+"') and "+str);
        if ((ui->comboBox->currentText() == "")&& (ui->comboBox_2->currentText() != ""))
            model->setFilter("unitId in (SELECT unitId FROM Real_estate_unit WHERE locality = '"+ui->comboBox_2->currentText()+"') and "+str);
        if ((ui->comboBox->currentText() == "")&& (ui->comboBox_2->currentText() == ""))
            model->setFilter(str);
    model->select();
    setHeaders();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->hideColumn(1);




}
// /////////////////////////////////////////////////////////////////////////////////////////
// purchases_opened() - слот открытия формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// /////////////////////////////////////////////////////////////////////////////////////////
void Purchases::purchases_opened()
{
    model->setFilter("custId = '"+QString::number(user.getUserName())+"'");
    show();
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_Delete_clicked() - кнопка удаления записи.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Purchases::on_Delete_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
    model->select();
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
void Purchases::fillComboBox()
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
void Purchases::on_pushButton_2_clicked()
{
    fillComboBox();
}
// /////////////////////////////////////////////////////////////////////////////////////////
// setHeaders() - установление заголовков столбцов.
//
// Локальные переменные:
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Purchases::setHeaders()
{
    model->setHeaderData(0, Qt::Horizontal, "Номер \n договора");
    model->setHeaderData(2, Qt::Horizontal, "Номер объекта");
    model->setHeaderData(3, Qt::Horizontal, "Итоговая \n cтоимость");
    model->setHeaderData(4, Qt::Horizontal, "Дата \n покупки");
    model->setHeaderData(5, Qt::Horizontal, "Дата \n окончания \n скидки");
}
