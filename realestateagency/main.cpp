//Программа Real_estate_agency
//Учебная практкиа по профессиональному модулю МДК.03.01 Технология разработки программного обеспечения
//
//Разработал: Фуфарев Никита Радиславович
//Дата: 25.05.2019
//Программа написана на языке программирования С++ с использованием библиотеки QT
//Задание:
//Разработать информационную систему для агентства недвижимости. У агентства находится некоторое количество
//объектов жилой недвижимости различных стоимостей и типов. Все клиенты при обращении проходят обязательную
//регистрацию, при которой о них собирается стандартная информация. Система должна обеспечивать ведение
//списка объектов недвижимостей, покупателей и договоров покупки.
//1. Создание базы данных для информационной системы агентства недвижимости.
//Создать таблицы «Договор покупки», «Покупатель», «Объект недвижимости», «Таблица1», «Таблица2»
//Заполнить таблицы «Объект недвижимости», «Таблица1», «Таблица2».
//2. Создание пользовательских форм
//Создать формы «Объект недвижимости», «Форма1», «Форма2» соответствующие таблицам базы данных
//c возможностью просмотра, добавление, удаление, обновление записей таблиц.
//3. Создание формы договора покупки.
//На форме договора аренды осуществить :
//1). Поиск автомобиля по параметрам: «Параметр1», «Параметр2»;
//2). Рассчитать стоимость.
//Стоимость=( Объект_недвижимости. Стоимость )*Скидка
//Скидка действует до определенной даты;
//3)Сохранение и просмотр договоров покупки.
//4. Создание формы авторизации
//Создать форму для авторизации зарегистрированных
//пользователей.
//Необходимо предусмотреть возможность регистрации
//пользователей.
//При регистрации пароль должен отвечать следующим
//требованиям:
//- Минимум 7 символов;
//- Минимум 1 прописная буква;
//- Первые два символа номер варианта;
//- Минимум один символ из набора: ! @ # $ % ^.
//
// Используемые переменные:
// a - управляет потоком управления приложения GUI и основными настройками;
// w - главная форма приложения;
// window - форма авторизации;
// windowTable - форма просмотра объектов недвижимости;
// purchaseWindow - форма просмотра договоров недвижимости;
// userWindow - форма просмотра пользователей;
// localityWindow - форма с параметрами;
// floorWindow - форма с параметрами;
// registerWindow - форма регистрации;
//
// Используемые функции:
// connection() - соединение с базой данных
// connect() - взаимодействие функций разных форм
// ////////////////////////////////////////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "autorization.h"
#include <QApplication>
#include <QDebug>
#include <QtSql>
#include <QTableView>
#include "dialog.h"
#include "database.h"
#include "users.h"
#include "purchases.h"
#include "locality.h"
#include "floor_covering.h"
#include "registration.h"
#include "agreement_accept.h"

extern currentUser user;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Соединение с базой данных
    connection();
    //Создание формы авторизации
    autorization window;
    window.show();
    //Создание главной формы
    MainWindow w;
    //Создание формы объектов недвижимости
    Dialog windowTable;
    //Создание формы договоров
    Purchases purchaseWindow;
    //Создание формы пользователей
    Users userWindow;
    //Создание формы параметров
    Locality localityWindow;
    //Создание формы параметров
    floor_covering floorWindow;
    //Создание формы регистрации
    Registration registerWindow;
    //Соединение функций разных форм
    agreement_accept acceptWindow;

    QObject::connect(&window, SIGNAL(autorized()), &w, SLOT(autorizationMessage()));
    QObject::connect(&w, SIGNAL(real_estate_open()), &windowTable, SLOT(real_estate_opened()));
    QObject::connect(&w, SIGNAL(purchases_open()), &purchaseWindow, SLOT(purchases_opened()));
    QObject::connect(&w, SIGNAL(users_open()), &userWindow, SLOT(users_opened()));
    QObject::connect(&w, SIGNAL(locality_open()), &localityWindow, SLOT(locality_opened()));
    QObject::connect(&w, SIGNAL(floor_covering_open()), &floorWindow, SLOT(floor_covering_opened()));
    QObject::connect(&window, SIGNAL(registration()), &registerWindow, SLOT(start_registration()));
    QObject::connect(&purchaseWindow, SIGNAL(purch_update()), &windowTable, SLOT(purchase_update()));
    QObject::connect(&windowTable, SIGNAL(open_agreement_accept(QString, QString, QString,  QString,
                                                                     QString, QString, QString, QString,
                                                                     QString)), &acceptWindow,
                     SLOT(start_form(QString, QString, QString,
                                     QString,
                                     QString, QString, QString,
                                     QString,
                                     QString)));
    QObject::connect(&acceptWindow, SIGNAL(accept_agreement()), &windowTable, SLOT(accept_agreement1()));
    //Запуск обработчика графического интерфейса
    return a.exec();
}
