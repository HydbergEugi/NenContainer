// Используемые функции:
// Locality(QWidget *parent) - инициализация формы;
// ~Locality() - удаление формы;
// on_insert_clicked() - кнопка добавления записи;
// on_Delete_clicked() - кнопка удаления записи;
// locality_opened() - слот открытия формы.

#include "locality.h"
#include "ui_locality.h"
// /////////////////////////////////////////////////////////////////////////////////////////
// Locality(QWidget *parent) - инициализация формы.
//
// Формальные параметры:
// *parent - ссылка на родительское окно.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы;
// /////////////////////////////////////////////////////////////////////////////////////////
Locality::Locality(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Locality)
{
    ui->setupUi(this);
    setWindowTitle("Изменение параметра");
    model = new QSqlTableModel;
    model->setTable("locality");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, "Номер");
    model->setHeaderData(1, Qt::Horizontal, "Город");
    ui->tableView->setModel(model);
}
// /////////////////////////////////////////////////////////////////////////////////////////
// ~Locality() - удаление формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
Locality::~Locality()
{
    delete ui;
}
// /////////////////////////////////////////////////////////////////////////////////////////
// locality_opened() - слот открытия формы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Locality::locality_opened()
{
    show();
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_insert_clicked() - добавление новой записи.
//
// Локальные переменные:
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Locality::on_insert_clicked()
{
    model->insertRows(model->rowCount(),1);
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_Delete_clicked() - удаление записи.
//
// Локальные переменные:
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Locality::on_Delete_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
    model->select();
}
