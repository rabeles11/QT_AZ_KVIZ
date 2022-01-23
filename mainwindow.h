#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QAbstractButton"
#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QDir>
#include <QMessageBox>
#include <iostream>
#include <QTimeLine>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow * getMainWinPtr();
    QSqlDatabase db;

    struct Player{
        int PositiveReply;
        bool is_on_turn;
        //QVector<QPushButton*> buttonList;
        QList<QString> buttonList;
        bool left;
        bool right;
        bool bottom;
        //QList<QButtonGroup> testbutton;
    };

    struct Player Player1 = {
        0,true,{},false,false,false
    };
    struct Player Player2 = {
        0,false,{},false,false,false
    };

    QList<QAbstractButton*> p1;
    QList<QAbstractButton*> p2;
    QAbstractButton *buttonss;
    //QPushButton* buttonss;
    QTimeLine *timeLine = new QTimeLine(1000, this);
    QList<QList<QString>> list = {};
    QList<QList<QString>> listgrey = {};
    int excel = 0;


/*
private slots:
    void on_pushButton_clicked();
*/
private:
    Ui::MainWindow *ui;
    static MainWindow * pMainWindow;


public slots:
    //void on_pushButton_clicked();
    void pbSetColorRed();
    void pbSetColorGreen();
    void pbSetColorGrey();
    void time_out();

   // void buttonWasClicked(int);
private slots:
    //QMenu *actionNahr_t_hlavn_ot_zky;
    //void on_pushButton_2_clicked();
    void on_actionNahr_t_hlavn_ot_zky_triggered();
};

#endif // MAINWINDOW_H
