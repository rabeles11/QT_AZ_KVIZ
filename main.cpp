#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QDir>
#include <QMessageBox>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
