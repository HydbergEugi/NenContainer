#ifndef DATABASE_H
#define DATABASE_H
#include <QDialog>
#include <QDebug>
#include <QtSql>



void connection();
void connection(QString connectionName);
QString deleteGaps(QString string);

#endif // DATABASE_H
