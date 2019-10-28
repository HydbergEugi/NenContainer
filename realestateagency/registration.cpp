// Используемые переменные:
// user - информация о текущем пользователе.
//
// Используемые функции:
// Registration(QWidget *parent) - инициализация формы;
// ~Registration() - удаление формы;
// on_Submit_clicked() - кнопка завершения регистрации;
// start_registration() - слот открытия формы.

#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>

// /////////////////////////////////////////////////////////////////////////////////////////
// Registration(QWidget *parent) - инициализация формы.
//
// Формальные параметры:
// *parent - ссылка на родительское окно.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    setWindowTitle("Регистрация");
}
// /////////////////////////////////////////////////////////////////////////////////////////
// ~Registration() - удаление формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
Registration::~Registration()
{
    delete ui;
}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_Submit_clicked() - кнопка завершения регистрации.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса;
// query - запрос ввода в базу данных;
// custQuery - запрос выборки из базы данных;
// custId - id пользователя;
// name - имя;
// surName - фамилия;
// patronymic - отчество;
// adress - адрес;
// number - номер телефона;
// password - пароль;
// rx - шаблон регулярного выражения;
// /////////////////////////////////////////////////////////////////////////////////////////
void Registration::on_Submit_clicked()
{
    QSqlQuery query;
    QSqlQuery custQuery;

    QString insertCustomer = "INSERT INTO customer"
                  "VALUES(%1, '%2', '%3', '%4', '%5', '%6','%7');";
    custQuery.exec("SELECT custId FROM customer");
    QSqlRecord custRec = custQuery.record();
    custQuery.last();
    int custId = custQuery.value(custRec.indexOf("custId")).toInt()+1;
    QString name = ui->Name->text();
    QString surname = ui->Surname->text();
    QString patronymic = ui->Patronymic->text();
    QString adress = ui->Adress->text();
    QString number = ui->Number->text();
    QString password = ui->Password->text();
    insertCustomer = insertCustomer.arg(custId).arg(surname).arg(name).arg(patronymic).arg(adress).arg(number).arg(password);
    QRegExp rx("^(?=.*[A-Z].*[A-Z])(?=.*[!@#$&%^])(?=.*[0-9].*[0-9])(?=.*[a-z].*[a-z].*[a-z]).{8}$");
    if (password.contains(rx))
   {
        query.exec(insertCustomer);
        QMessageBox::information(this, "Регистрация", "Регистрация прошла успешно");
    }
    else
    {
       QMessageBox::warning(this, "Ошибка ввода пароля", "Пароль должен содержать номер варианта, одну прописную букву"
                                                         ", специальные символы !@#$&%^ и содержать не менее 7 символов");
    }

}
// /////////////////////////////////////////////////////////////////////////////////////////
// start_registration() - слот открытия формы.
// /////////////////////////////////////////////////////////////////////////////////////////
void Registration::start_registration()
{
    show();
}
