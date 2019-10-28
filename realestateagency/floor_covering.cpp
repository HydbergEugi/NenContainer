
// Используемые функции:
// floor_covering(QWidget *parent) - инициализация формы;
// ~floor_covering() - удаление формы;
// on_insert_clicked() - кнопка добавления записи;
// on_delete_2_clicked() - кнопка удаления записи;
// floor_covering_opened() - слот открытия формы.

#include "floor_covering.h"
#include "ui_floor_covering.h"

// /////////////////////////////////////////////////////////////////////////////////////////
// floor_covering(QWidget *parent) - инициализация формы.
//
// Формальные параметры:
// *parent - ссылка на родительское окно.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// model - модель таблицы;
// /////////////////////////////////////////////////////////////////////////////////////////
floor_covering::floor_covering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::floor_covering)
{
    ui->setupUi(this);
    setWindowTitle("Изменение параметра");
    model = new QSqlTableModel;
    model->setTable("floor_covering");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, "Номер");
    model->setHeaderData(1, Qt::Horizontal, "Покрытие");
    ui->tableView->setModel(model);
}
// /////////////////////////////////////////////////////////////////////////////////////////
// ~floor_covering() - удаление формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
floor_covering::~floor_covering()
{
    delete ui;
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_insert_clicked() - добавление новой записи.
//
// Локальные переменные:
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void floor_covering::on_insert_clicked()
{
    model->insertRows(model->rowCount(),1);
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_delete_2_clicked() - удаление записи.
//
// Локальные переменные:
// model - модель таблицы.
// /////////////////////////////////////////////////////////////////////////////////////////
void floor_covering::on_delete_2_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
    model->select();
}
// /////////////////////////////////////////////////////////////////////////////////////////
// floor_covering_opened() - слот открытия формы.
// /////////////////////////////////////////////////////////////////////////////////////////
void floor_covering::floor_covering_opened()
{
    show();
}
