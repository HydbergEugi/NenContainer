#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool admin;

private slots:
    void autorizationMessage();
    void on_Real_estate_clicked();

    void on_Agreements_clicked();

    void on_Users_clicked();

    void on_locality_clicked();

    void on_floor_covering_clicked();


signals:
    void real_estate_open();
    void purchases_open();
    void users_open();
    void floor_covering_open();
    void locality_open();
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
