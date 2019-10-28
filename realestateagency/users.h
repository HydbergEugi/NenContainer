#ifndef USERS_H
#define USERS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "database.h"

class currentUser
{
public:
    int getUserName();
    void setUserName(int id);
private:
    int userId = -1;
};

namespace Ui {
class Users;
}

class Users : public QDialog
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr);
    ~Users();

public slots:
    void users_opened();
private:
    Ui::Users *ui;
    QSqlQuery query;
    QSqlTableModel *model;
};



#endif // USERS_H
