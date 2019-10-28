// Используемые переменные:
// user - информация о текущем пользователе.
//
// Используемые функции:
// autorization() - инициализация формы;
// ~autorization() - удаление формы;
// on_pushButton_clicked() - кнопка авторизации;
// on_Registration_clicked() - сигнал о нажатии кнопки регистрации.

#include "autorization.h"
#include "ui_autorization.h"
#include "mainwindow.h"
#include "database.h"
#include <QMessageBox>
#include "users.h"

currentUser user;

// /////////////////////////////////////////////////////////////////////////////////////////
// autorization(QWidget *parent) - инициализация формы.
//
// Формальные параметры:
// *parent - ссылка на родительское окно.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
autorization::autorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::autorization)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");

}
// /////////////////////////////////////////////////////////////////////////////////////////
// ~autorization() - удаление формы.
//
// Локальные переменные:
// ui - переменная пользовательского интерфейса.
// /////////////////////////////////////////////////////////////////////////////////////////
autorization::~autorization()
{
    delete ui;
}

// /////////////////////////////////////////////////////////////////////////////////////////
// on_pushButton_clicked() - кнопка авторизации.
//
// Локальные переменные:
// query - запрос;
// rec - запись результатов запроса;
// name - имя из базы данных;
// password - пароль из базы данных;
// nameEntered - введённое имя;
// passwordEntered - введённый пароль;
// /////////////////////////////////////////////////////////////////////////////////////////
void autorization::on_pushButton_clicked()
{

    QSqlQuery query;
    query.exec("SELECT custId, name, password FROM customer");

    QSqlRecord rec = query.record();

    QString name;
    QString password;
    QString nameEntered = ui->login->text();
    QString passwordEntered = ui->password->text();

    while (query.next())
    {
        name = query.value(rec.indexOf("name")).toString();
        password = query.value(rec.indexOf("password")).toString();
        name.replace(" ", "");
        password.replace(" ", "");
        qDebug() <<  name << " " << password;
        if (( name == nameEntered  ) && (password == passwordEntered))
        {
            user.setUserName(query.value(rec.indexOf("custId")).toInt());
            emit autorized();
            hide();
            break;
        }
    }
    if (!(( name == nameEntered  ) && (password == passwordEntered)))
        QMessageBox::warning(this, "Ошибка входа", "Неправильный логин или пароль");


}
// /////////////////////////////////////////////////////////////////////////////////////////
// on_Registration_clicked() - сигнал о нажатии кнопки регистрации.
// /////////////////////////////////////////////////////////////////////////////////////////
void autorization::on_Registration_clicked()
{
    emit registration();
}
