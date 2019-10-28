#include <QApplication>
#include <QDebug>
#include <QtSql>
#include "mainwindow.h"
#include "autorization.h"
#include "database.h"

//СОЕДИНЕНИЕ С БАЗОЙ ДАННЫХ
// //////////////////////////////////////////////////////////////////////////////////////////////////////


void connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    db.setHostName("imagination");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=imagination\\Bospor;DATABASE=Real_estate_agency;");
    db.setUserName("sa");
    db.setPassword("rfdfvfwe");
    bool ok  = db.open();
    if (!ok)
    {
        qDebug() << "Cannot open database:" << db.lastError();

    }
    else
    {
        qDebug() << "Success!!";
    }
}


// //////////////////////////////////////////////////////////////////////////////////////////////////////

//УДАЛЕНИЕ ПРОБЕЛОВ ИЗ КОНЦА
// //////////////////////////////////////////////////////////////////////////////////////////////////////
QString deleteGaps(QString string)
{
    for (int i=string.size()-1; i>=0; i--)
    {
        if (string.at(i).isSpace())
            string.remove(i,1);
        else {
            break;
        }
    }
    return string;
}
