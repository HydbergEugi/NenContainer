#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QDialog>
#include "users.h"

namespace Ui {
class autorization;
}

class autorization : public QDialog
{
    Q_OBJECT

public:
    explicit autorization(QWidget *parent = nullptr);
    ~autorization();

private slots:
    void on_pushButton_clicked();

    void on_Registration_clicked();

signals:
    void autorized();
    void registration();
private:
    Ui::autorization *ui;
};


#endif // AUTORIZATION_H
