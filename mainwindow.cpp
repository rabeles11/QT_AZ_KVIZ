#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "questionwindow.h"
#include "greyquestion.h"
#include "QTimeLine"
#include "QButtonGroup"
#include <iostream>
#include "QColor"
#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>
#include <QtSql/QSqlError>
#include <QFileDialog>
#include <QList>
#include <algorithm>
#include <random>
#include "QDebug"
#include <sstream>
#include <string>
#include <QPushButton>
#include <QPropertyAnimation>
using namespace std;

MainWindow * MainWindow::pMainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pMainWindow = this;
    // Tady pořešit ten timing!!!
    //QTimeLine *timeLine = new QTimeLine(100000, this);
    ui->progressBar->setRange(0,100);
    timeLine->setDuration(1200000);
    //timeLine->setDuration(10000);

    timeLine->setFrameRange(0, 100);
    timeLine->setEndFrame(100);
    timeLine->start();

    connect(timeLine, &QTimeLine::frameChanged, ui->progressBar, &QProgressBar::setValue);

    /*
    connect(timeLine, &QTimeLine::frameChanged, [&](int value) {
        ui->progressBar->setValue(value);
        qDebug() << "Test";
    });
    */
    connect(timeLine,&QTimeLine::finished,[this]() {
        cout << "Dopočítalo se!!" << endl;
        time_out();});

    //ui->pushButton->setStyleSheet("background-color:yellow");
    /*
    QPropertyAnimation *animation= new QPropertyAnimation(ui->pushButton, "background-color");
    animation->setDuration(1000);
    animation->setStartValue(QColor("yellow"));
    animation->setEndValue(QColor("green"));
    animation->start();
    */

    ui->pushButton->setToolTip("Left and Right");
    ui->pushButton_2->setToolTip("Left");
    ui->pushButton_4->setToolTip("Left");
    ui->pushButton_7->setToolTip("Left");
    ui->pushButton_11->setToolTip("Left");
    ui->pushButton_16->setToolTip("Left");
    ui->pushButton_22->setToolTip("Left and Bottom");

    ui->pushButton_3->setToolTip("Right");
    ui->pushButton_6->setToolTip("Right");
    ui->pushButton_10->setToolTip("Right");
    ui->pushButton_15->setToolTip("Right");
    ui->pushButton_21->setToolTip("Right");
    ui->pushButton_28->setToolTip("Right and Bottom");

    ui->pushButton_23->setToolTip("Bottom");
    ui->pushButton_24->setToolTip("Bottom");
    ui->pushButton_25->setToolTip("Bottom");
    ui->pushButton_26->setToolTip("Bottom");
    ui->pushButton_27->setToolTip("Bottom");


    QButtonGroup* group = new QButtonGroup(this);
    group->addButton(ui->pushButton);
    group->addButton(ui->pushButton_2);
    group->addButton(ui->pushButton_3);
    group->addButton(ui->pushButton_4);
    group->addButton(ui->pushButton_5);
    group->addButton(ui->pushButton_6);
    group->addButton(ui->pushButton_7);
    group->addButton(ui->pushButton_8);
    group->addButton(ui->pushButton_9);
    group->addButton(ui->pushButton_10);
    group->addButton(ui->pushButton_11);
    group->addButton(ui->pushButton_12);
    group->addButton(ui->pushButton_13);
    group->addButton(ui->pushButton_14);
    group->addButton(ui->pushButton_15);
    group->addButton(ui->pushButton_16);
    group->addButton(ui->pushButton_17);
    group->addButton(ui->pushButton_18);
    group->addButton(ui->pushButton_19);
    group->addButton(ui->pushButton_20);
    group->addButton(ui->pushButton_21);
    group->addButton(ui->pushButton_22);
    group->addButton(ui->pushButton_23);
    group->addButton(ui->pushButton_24);
    group->addButton(ui->pushButton_25);
    group->addButton(ui->pushButton_26);
    group->addButton(ui->pushButton_27);
    group->addButton(ui->pushButton_28);
    ui->labelImage->hide();


    // Dej info o tlačítkách dohromady!!

    //QVector<QPushButton*> allButtonsList;
    //QVector<QVector<QPushButton*>> allButtonsList;
    QMap<QAbstractButton*,QVector<QAbstractButton*>> allbuttonsMap;
    QVector<QAbstractButton*> ConnectedButtons;
    //QMap<QPushButton*,QVector<QPushButton*>> allbuttonsMap;
    //QVector<QPushButton*> ConnectedButtons;
    //
    // BUtton 1
    ConnectedButtons.append(ui->pushButton_2);
    ConnectedButtons.append(ui->pushButton_3);
    allbuttonsMap[ui->pushButton]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 2
    ConnectedButtons.append(ui->pushButton);
    ConnectedButtons.append(ui->pushButton_3);
    ConnectedButtons.append(ui->pushButton_4);
    ConnectedButtons.append(ui->pushButton_5);
    allbuttonsMap[ui->pushButton_2]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 3
    ConnectedButtons.append(ui->pushButton);
    ConnectedButtons.append(ui->pushButton_2);
    ConnectedButtons.append(ui->pushButton_5);
    ConnectedButtons.append(ui->pushButton_6);
    allbuttonsMap[ui->pushButton_3]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 4
    ConnectedButtons.append(ui->pushButton_2);
    ConnectedButtons.append(ui->pushButton_5);
    ConnectedButtons.append(ui->pushButton_7);
    ConnectedButtons.append(ui->pushButton_8);
    allbuttonsMap[ui->pushButton_4]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 5
    ConnectedButtons.append(ui->pushButton_2);
    ConnectedButtons.append(ui->pushButton_3);
    ConnectedButtons.append(ui->pushButton_4);
    ConnectedButtons.append(ui->pushButton_6);
    ConnectedButtons.append(ui->pushButton_8);
    ConnectedButtons.append(ui->pushButton_9);
    allbuttonsMap[ui->pushButton_5]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 6
    ConnectedButtons.append(ui->pushButton_3);
    ConnectedButtons.append(ui->pushButton_5);
    ConnectedButtons.append(ui->pushButton_9);
    ConnectedButtons.append(ui->pushButton_10);
    allbuttonsMap[ui->pushButton_6]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 7
    ConnectedButtons.append(ui->pushButton_4);
    ConnectedButtons.append(ui->pushButton_8);
    ConnectedButtons.append(ui->pushButton_11);
    ConnectedButtons.append(ui->pushButton_12);
    allbuttonsMap[ui->pushButton_7]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 8
    ConnectedButtons.append(ui->pushButton_4);
    ConnectedButtons.append(ui->pushButton_5);
    ConnectedButtons.append(ui->pushButton_7);
    ConnectedButtons.append(ui->pushButton_9);
    ConnectedButtons.append(ui->pushButton_12);
    ConnectedButtons.append(ui->pushButton_13);
    allbuttonsMap[ui->pushButton_8]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 9
    ConnectedButtons.append(ui->pushButton_5);
    ConnectedButtons.append(ui->pushButton_6);
    ConnectedButtons.append(ui->pushButton_8);
    ConnectedButtons.append(ui->pushButton_10);
    ConnectedButtons.append(ui->pushButton_13);
    ConnectedButtons.append(ui->pushButton_14);
    allbuttonsMap[ui->pushButton_9]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 10
    ConnectedButtons.append(ui->pushButton_6);
    ConnectedButtons.append(ui->pushButton_9);
    ConnectedButtons.append(ui->pushButton_14);
    ConnectedButtons.append(ui->pushButton_15);
    allbuttonsMap[ui->pushButton_10]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 11
    ConnectedButtons.append(ui->pushButton_7);
    ConnectedButtons.append(ui->pushButton_8);
    ConnectedButtons.append(ui->pushButton_12);
    ConnectedButtons.append(ui->pushButton_16);
    ConnectedButtons.append(ui->pushButton_17);
    allbuttonsMap[ui->pushButton_11]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 12
    ConnectedButtons.append(ui->pushButton_7);
    ConnectedButtons.append(ui->pushButton_8);
    ConnectedButtons.append(ui->pushButton_11);
    ConnectedButtons.append(ui->pushButton_13);
    ConnectedButtons.append(ui->pushButton_17);
    ConnectedButtons.append(ui->pushButton_18);
    allbuttonsMap[ui->pushButton_12]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 13
    ConnectedButtons.append(ui->pushButton_8);
    ConnectedButtons.append(ui->pushButton_9);
    ConnectedButtons.append(ui->pushButton_12);
    ConnectedButtons.append(ui->pushButton_14);
    ConnectedButtons.append(ui->pushButton_18);
    ConnectedButtons.append(ui->pushButton_19);
    allbuttonsMap[ui->pushButton_13]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 14
    ConnectedButtons.append(ui->pushButton_9);
    ConnectedButtons.append(ui->pushButton_10);
    ConnectedButtons.append(ui->pushButton_13);
    ConnectedButtons.append(ui->pushButton_15);
    ConnectedButtons.append(ui->pushButton_19);
    ConnectedButtons.append(ui->pushButton_20);
    allbuttonsMap[ui->pushButton_14]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 15
    ConnectedButtons.append(ui->pushButton_10);
    ConnectedButtons.append(ui->pushButton_14);
    ConnectedButtons.append(ui->pushButton_20);
    ConnectedButtons.append(ui->pushButton_21);
    allbuttonsMap[ui->pushButton_15]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 16
    ConnectedButtons.append(ui->pushButton_11);
    ConnectedButtons.append(ui->pushButton_17);
    ConnectedButtons.append(ui->pushButton_22);
    ConnectedButtons.append(ui->pushButton_23);
    allbuttonsMap[ui->pushButton_16]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 17
    ConnectedButtons.append(ui->pushButton_11);
    ConnectedButtons.append(ui->pushButton_12);
    ConnectedButtons.append(ui->pushButton_16);
    ConnectedButtons.append(ui->pushButton_18);
    ConnectedButtons.append(ui->pushButton_23);
    ConnectedButtons.append(ui->pushButton_24);
    allbuttonsMap[ui->pushButton_17]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 18
    ConnectedButtons.append(ui->pushButton_12);
    ConnectedButtons.append(ui->pushButton_13);
    ConnectedButtons.append(ui->pushButton_17);
    ConnectedButtons.append(ui->pushButton_19);
    ConnectedButtons.append(ui->pushButton_24);
    ConnectedButtons.append(ui->pushButton_25);
    allbuttonsMap[ui->pushButton_18]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 19
    ConnectedButtons.append(ui->pushButton_13);
    ConnectedButtons.append(ui->pushButton_14);
    ConnectedButtons.append(ui->pushButton_18);
    ConnectedButtons.append(ui->pushButton_20);
    ConnectedButtons.append(ui->pushButton_25);
    ConnectedButtons.append(ui->pushButton_26);
    allbuttonsMap[ui->pushButton_19]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 20
    ConnectedButtons.append(ui->pushButton_14);
    ConnectedButtons.append(ui->pushButton_15);
    ConnectedButtons.append(ui->pushButton_19);
    ConnectedButtons.append(ui->pushButton_21);
    ConnectedButtons.append(ui->pushButton_26);
    ConnectedButtons.append(ui->pushButton_27);
    allbuttonsMap[ui->pushButton_20]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 21
    ConnectedButtons.append(ui->pushButton_15);
    ConnectedButtons.append(ui->pushButton_20);
    ConnectedButtons.append(ui->pushButton_27);
    ConnectedButtons.append(ui->pushButton_28);
    allbuttonsMap[ui->pushButton_21]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 22
    ConnectedButtons.append(ui->pushButton_16);
    ConnectedButtons.append(ui->pushButton_23);
    allbuttonsMap[ui->pushButton_22]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 23
    ConnectedButtons.append(ui->pushButton_16);
    ConnectedButtons.append(ui->pushButton_17);
    ConnectedButtons.append(ui->pushButton_23);
    ConnectedButtons.append(ui->pushButton_24);
    allbuttonsMap[ui->pushButton_23]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 24
    ConnectedButtons.append(ui->pushButton_17);
    ConnectedButtons.append(ui->pushButton_18);
    ConnectedButtons.append(ui->pushButton_23);
    ConnectedButtons.append(ui->pushButton_25);
    allbuttonsMap[ui->pushButton_24]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 25
    ConnectedButtons.append(ui->pushButton_18);
    ConnectedButtons.append(ui->pushButton_19);
    ConnectedButtons.append(ui->pushButton_24);
    ConnectedButtons.append(ui->pushButton_26);
    allbuttonsMap[ui->pushButton_25]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 26
    ConnectedButtons.append(ui->pushButton_19);
    ConnectedButtons.append(ui->pushButton_20);
    ConnectedButtons.append(ui->pushButton_25);
    ConnectedButtons.append(ui->pushButton_27);
    allbuttonsMap[ui->pushButton_26]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 27
    ConnectedButtons.append(ui->pushButton_20);
    ConnectedButtons.append(ui->pushButton_21);
    ConnectedButtons.append(ui->pushButton_26);
    ConnectedButtons.append(ui->pushButton_28);
    allbuttonsMap[ui->pushButton_27]=ConnectedButtons;
    ConnectedButtons.clear();
    //Button 28
    ConnectedButtons.append(ui->pushButton_21);
    ConnectedButtons.append(ui->pushButton_27);
    allbuttonsMap[ui->pushButton_28]=ConnectedButtons;
    ConnectedButtons.clear();

    qDebug() << allbuttonsMap; // button 1 a sousedi
    /*
    QVector<QPushButton*> buttonseee;
    allButtonsList.append(ui->pushButton_15);
    allButtonsList.append(ui->pushButton_14);
    qDebug() << "přidávám";
    qDebug() << allButtonsList;
    qDebug() << allButtonsList[1];
    */
    qDebug() << "POZOOOOOOOR";
   // qDebug() << allbuttonsMap[0].contains("pushButton_23");
    qDebug() << allbuttonsMap.keys();


    connect(group, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
        [=](QAbstractButton *button){

                                        if(Player1.left and Player1.right and Player1.bottom){         //tady se nikdy nedostanu pozor!!
                                            qDebug() << "Hráč 1 má 3 strany checkni si jestli nevyhrál";
                                            qDebug() << Player1.buttonList;
                                            qDebug() << p1;
                                            int Player1AlreadyWin = 0;
                                            for( int i=0; i<p1.count(); ++i )                         // tady projiždím všechny tlačitka co má hráč! od prvního co si vzal!
                                            {
                                                if(Player1AlreadyWin == 1)                            // tady to zrus pokud už našel výherní cestu!!
                                                {
                                                    break;
                                                }
                                                QList<QAbstractButton *> AlreadyVisited = {};         // tyhle tlačítka sem již navšítvil
                                                QList<QAbstractButton *> HavetoVisit = {};            // Tyhle tlačitka mám navštivit, protože mají stejnou barvu a ještě sem tam nebyl
                                                QAbstractButton* NewNode = p1[i];
                                                int LeftConnected = 0;
                                                int RighConnected = 0;
                                                int BottomConnected = 0;
                                                while(true){
                                                                                                    // Tady začínám ukládat o jakou pozici tlačítka se jedná a jestli není okrajové!!
                                                    if(NewNode->toolTip() == "Left")
                                                    {
                                                        //qDebug() << "nastavuju Left";
                                                        LeftConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Right")
                                                    {
                                                        //qDebug() << "nastavuju Right";
                                                        RighConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Bottom")
                                                    {
                                                        //qDebug() << "nastavuju bot";
                                                        BottomConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Right and Bottom")
                                                    {
                                                        //qDebug() << "nastavuju Right and Bot";
                                                        RighConnected = 1;
                                                        BottomConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Left and Bottom")
                                                    {
                                                        //qDebug() << "nastavuju Left and bot";
                                                        LeftConnected = 1;
                                                        BottomConnected = 1;

                                                    }
                                                    else if(NewNode->toolTip() == "Left and Right")
                                                    {
                                                        //qDebug() << "nastavuju Left and right";
                                                        RighConnected = 1;
                                                        LeftConnected = 1;
                                                    }
                                                                                                                     //tady končí okrajové hledání tlačítek!
                                                    for (QAbstractButton* x : allbuttonsMap.value(NewNode)){        // tady projiždím všechny sousedy na tom kořenu!!
                                                            if(AlreadyVisited.contains(NewNode) == false){
                                                                AlreadyVisited.append(NewNode);                         // tady přidávám do listu alreadyvisited ten node!!
                                                            }
                                                            if(x->palette().color(QPalette::Button) == "Green"       // Chci přidat jen ty X, kde sedí barva a ještě jsem tam nebyl!! a zárověn ještě není v listu havetovisit!
                                                               && AlreadyVisited.contains(x) == false
                                                                    && HavetoVisit.contains(x) == false)
                                                            {
                                                                HavetoVisit.append(x);                                  // tady přidávám do HaveToVisit ty, kam mám jít tj zelená barva! a nebyl sem tam!
                                                            }
                                                    }
                                                    qDebug () << "Výherní cesta";
                                                    qDebug () << AlreadyVisited;
                                                    if(HavetoVisit.isEmpty()){
                                                        if(LeftConnected == 1 && RighConnected == 1 && BottomConnected==1)
                                                        {
                                                            QString status = QString("Konec hry Player1 spojil tři strany a vyhrává s počtem %1 bodů").arg(Player1.PositiveReply);
                                                            QMessageBox::information(this, tr("Info"), status);
                                                            qDebug() << "Hráč vyhrál!! má 3 strany!!";
                                                            Player1AlreadyWin = 1;

                                                            for(QAbstractButton* x : AlreadyVisited)
                                                            {
                                                                x->setStyleSheet("background-color:yellow");
                                                            }
                                                            return;
                                                            break;
                                                        }
                                                        else{
                                                            qDebug() << "Ještě nemá spojeno!!";
                                                            break;
                                                        }
                                                    }
                                                    NewNode = HavetoVisit.first();                               // Jako NewNode nastavím první z listu, kde jsem nebyl
                                                    HavetoVisit.removeFirst();                                   // tady vyhodím první, z havetovisit
                                                }

                                            }
                                        }
                                        if(Player2.left and Player2.right and Player2.bottom){         //tady se nikdy nedostanu pozor!!
                                            qDebug() << "Hráč 2 má 3 strany checkni si jestli nevyhrál";
                                            qDebug() << Player2.buttonList;
                                            qDebug() << p2;
                                            int Player2AlreadyWin = 0;
                                            for( int i=0; i<p2.count(); ++i )                         // tady projiždím všechny tlačitka co má hráč! od prvního co si vzal!
                                            {
                                                if(Player2AlreadyWin == 1)                            // tady to zrus pokud už našel výherní cestu!!
                                                {
                                                    break;
                                                }
                                                QList<QAbstractButton *> AlreadyVisited = {};         // tyhle tlačítka sem již navšítvil
                                                QList<QAbstractButton *> HavetoVisit = {};            // Tyhle tlačitka mám navštivit, protože mají stejnou barvu a ještě sem tam nebyl
                                                QAbstractButton* NewNode = p2[i];
                                                int LeftConnected = 0;
                                                int RighConnected = 0;
                                                int BottomConnected = 0;
                                                while(true){
                                                                                                    // Tady začínám ukládat o jakou pozici tlačítka se jedná a jestli není okrajové!!
                                                    if(NewNode->toolTip() == "Left")
                                                    {
                                                        //qDebug() << "nastavuju Left";
                                                        LeftConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Right")
                                                    {
                                                        //qDebug() << "nastavuju Right";
                                                        RighConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Bottom")
                                                    {
                                                        //qDebug() << "nastavuju bot";
                                                        BottomConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Right and Bottom")
                                                    {
                                                        //qDebug() << "nastavuju Right and Bot";
                                                        RighConnected = 1;
                                                        BottomConnected = 1;
                                                    }
                                                    else if(NewNode->toolTip() == "Left and Bottom")
                                                    {
                                                        //qDebug() << "nastavuju Left and bot";
                                                        LeftConnected = 1;
                                                        BottomConnected = 1;

                                                    }
                                                    else if(NewNode->toolTip() == "Left and Right")
                                                    {
                                                        //qDebug() << "nastavuju Left and right";
                                                        RighConnected = 1;
                                                        LeftConnected = 1;
                                                    }
                                                                                                                     //tady končí okrajové hledání tlačítek!
                                                    for (QAbstractButton* x : allbuttonsMap.value(NewNode)){        // tady projiždím všechny sousedy na tom kořenu!!
                                                            if(AlreadyVisited.contains(NewNode) == false){
                                                                AlreadyVisited.append(NewNode);                         // tady přidávám do listu alreadyvisited ten node!!
                                                            }
                                                            if(x->palette().color(QPalette::Button) == "Red"       // Chci přidat jen ty X, kde sedí barva a ještě jsem tam nebyl!! a zárověn ještě není v listu havetovisit!
                                                               && AlreadyVisited.contains(x) == false
                                                                    && HavetoVisit.contains(x) == false)
                                                            {
                                                                HavetoVisit.append(x);                                  // tady přidávám do HaveToVisit ty, kam mám jít tj zelená barva! a nebyl sem tam!
                                                            }
                                                    }
                                                    qDebug () << "Výherní cesta";
                                                    qDebug () << AlreadyVisited;
                                                    if(HavetoVisit.isEmpty()){
                                                        if(LeftConnected == 1 && RighConnected == 1 && BottomConnected==1)
                                                        {
                                                            QString status = QString("Konec hry Player2 spojil tři strany a vyhrává s počtem %1 bodů").arg(Player2.PositiveReply);
                                                            QMessageBox::information(this, tr("Info"), status);
                                                            qDebug() << "Hráč vyhrál!! má 3 strany!!";
                                                            Player2AlreadyWin = 1;

                                                            for(QAbstractButton* x : AlreadyVisited)
                                                            {
                                                                x->setStyleSheet("background-color:yellow");

                                                            }

                                                            return;
                                                            break;
                                                        }
                                                        else{
                                                            qDebug() << "Ještě nemá spojeno!!";
                                                            break;
                                                        }
                                                    }
                                                    NewNode = HavetoVisit.first();                               // Jako NewNode nastavím první z listu, kde jsem nebyl
                                                    HavetoVisit.removeFirst();                                   // tady vyhodím první, z havetovisit
                                                }

                                            }
                                        }

                                        QColor colorgrey("grey");
                                        QColor color = button->palette().color(QPalette::Button);
                                        //Player1.testbutton.append(*buttonss);
                                        //Player1.test->addButton(buttonss);
                                        //qDebug() << Player1.test;
                                        if(color == colorgrey){
                                            cout << "Grey button" << endl;
                                            buttonss = button;
                                            GreyQuestion *greyquestion = new GreyQuestion(this);
                                            greyquestion->setModal(true);
                                            greyquestion->show();
                                        }
                                        else{
                                            QuestionWindow *questionWindow = new QuestionWindow(this);
                                            questionWindow->setModal(true);
                                            questionWindow->show();
                                            cout << "You have clicked button: "<< button << endl;
                                            cout << "You have button color: "<< qPrintable(color.name()) << endl;
                                            buttonss = button;
                                        }
                                        });

    // setuping driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    if (db.lastError().isValid()){
        qCritical() << "addDatabase" << db.lastError().text();
    }

    // getting system app data folder
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // create the application data folder if it not exists
    QDir dir(appDataLocation);
    if(!dir.exists()){
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }

    //setup the db file name and open it
    QString dbPath = appDataLocation+"/Questions.db";
    dir.remove(appDataLocation+"/Questions.db");
    qDebug() << "dbPath" << dbPath;
    db.setDatabaseName(dbPath);
    db.open();
    qDebug() << db;
    if(!db.open()){
        qCritical() << "Unable to open db" << db.lastError().text() << dbPath;
    }

    // creating a table with QuestionMainGame
    QString tblFileCreate = "CREATE TABLE IF NOT EXISTS QuestionMainGame ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "Question STRING,"
                            "Expected_reply STRING,"
                            "WasQuestionUsed INT"
                            ")";
    QSqlQuery query;
    query.exec(tblFileCreate);

    if(query.lastError().isValid()){
        qWarning() << "CREATE TABLE" << query.lastError().text();
    }

    // creating a table with QuestionsYesOrNot
    tblFileCreate = "CREATE TABLE IF NOT EXISTS QuestionsYesOrNot ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "Question STRING,"
                            "Expected_reply STRING,"
                            "WasQuestionUsed INT"
                            ")";
    query.exec(tblFileCreate);

    if(query.lastError().isValid()){
        qWarning() << "CREATE TABLE" << query.lastError().text();
    }
    // INSERTING DATA INTO MAINGAME
    // inserting Data 1
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 2+2");
        query.bindValue(1, "4");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 2
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 4+4");
        query.bindValue(1, "8");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 3
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 1+1");
        query.bindValue(1, "2");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 4
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 4+1");
        query.bindValue(1, "5");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 5
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 1+3");
        query.bindValue(1, "4");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 6
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 10+11");
        query.bindValue(1, "21");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 7
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 21-1");
        query.bindValue(1, "20");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 8
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 14*2");
        query.bindValue(1, "28");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 9
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 14+14");
        query.bindValue(1, "28");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 10
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 111+1");
        query.bindValue(1, "112");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 11
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 122+1");
        query.bindValue(1, "123");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 12
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 100+100");
        query.bindValue(1, "200");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 13
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 400+1");
        query.bindValue(1, "401");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 14
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 99+1");
        query.bindValue(1, "100");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 15
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 99/99");
        query.bindValue(1, "1");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 16
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 0*5454");
        query.bindValue(1, "0");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 17
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 22+44");
        query.bindValue(1, "66");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 18
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 88+22");
        query.bindValue(1, "110");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 19
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 144+1");
        query.bindValue(1, "145");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 20
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 145-1");
        query.bindValue(1, "144");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 21
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 1444+1");
        query.bindValue(1, "1445");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 22
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 1000-1");
        query.bindValue(1, "999");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 23
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 444+444");
        query.bindValue(1, "888");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 24
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 110*1");
        query.bindValue(1, "110");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 25
    query.prepare("INSERT INTO QuestionMainGame (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Kolik je 1122-1000");
        query.bindValue(1, "122");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }

    // END OF INSERTING DATA INTO MAINGAME

    // START OF INSERTING DATA INTO BONUS GAME
    // inserting Data 1
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Je zeman prezidentem?");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 2
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Je babiš premiér");
        query.bindValue(1, "Ne");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 3
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Je UTB vysoká škola");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 4
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Je tato aplikace multiplatformní");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 5
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "4+4 = 8");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 6
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "8+8 = 12");
        query.bindValue(1, "Ne");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 7
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "4*6+4 = 28");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 8
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "9*9 = 82");
        query.bindValue(1, "Ne");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 9
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Je česká republika stát?");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 10
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Je Rusko považováno za demokracii?");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 11
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Líbí se vám tato hra");
        query.bindValue(1, "Ano");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 12
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "9*4 = 44");
        query.bindValue(1, "Ne");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 13
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "40*0 = 40");
        query.bindValue(1, "Ne");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }
    // inserting Data 14
    query.prepare("INSERT INTO QuestionsYesOrNot (Question, Expected_reply, WasQuestionUsed) "
                      "VALUES (:questin, :expected_reply, :wasquestionused)");
        query.bindValue(0, "Je ano vítežem posledních voleb?");
        query.bindValue(1, "Ne");
        query.bindValue(2, 1);
        query.exec();
    if(query.lastError().isValid()){
            qWarning() << "INSERT" << query.lastError().text();
        }

    // END OF INSERTING DATA INTO BONUS GAME

    // selecting data
    QString sqlSelect = "SELECT * FROM QuestionMainGame ORDER BY random()";
    query.exec(sqlSelect);

    if(query.lastError().isValid()){
            qWarning() << "SELECT" << query.lastError().text();
        }
    while(query.next()){
        QString Question = query.value("Question").toString();
        QString QuestionExpected = query.value("Expected_reply").toString();
        cout << Question.toStdString() << endl;
        cout << QuestionExpected.toStdString() << endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::getMainWinPtr()
{
    return pMainWindow;
}

void MainWindow::pbSetColorRed()
{
    buttonss->setStyleSheet("background-color:red");
}
void MainWindow::pbSetColorGreen()
{
     buttonss->setStyleSheet("background-color:green");
}
void MainWindow::pbSetColorGrey()
{
     buttonss->setStyleSheet("background-color:grey");
}
void MainWindow::time_out()
{
    if(Player1.PositiveReply > Player2.PositiveReply){
        QString status = QString("Vypršel čas!! Player 1 vyhrává s počtem %1 bodů").arg(Player1.PositiveReply);
        QMessageBox::information(this, tr("Info"), status);
    }
    else{
        QString status = QString("Vypršel čas!! Player 2 vyhrává s počtem %1 bodů").arg(Player2.PositiveReply);
        QMessageBox::information(this, tr("Info"), status);
    }


    cout << "pes" << endl;
}


void MainWindow::on_actionNahr_t_hlavn_ot_zky_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file", "C://");
    //QSqlDatabase dba = QSqlDatabase::addDatabase("QODBC", "excelexport");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    db.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + file_name);
    if(!db.isValid())
        {
            qDebug() << "ExportExcelObject::export2Excel failed: QODBC not supported.";
        }
    else{
        qDebug() << "Databáze je validní!";
    }
    if(!db.open())
        {
            qDebug() << "ExportExcelObject::export2Excel failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.";
            //QSqlDatabase::removeDatabase("excelexport");
        }
    else{
        qDebug() << "otevřeno!!";
    }
    //QSqlQuery query;
    QSqlQuery query("select * from [" + QString("Sheet1") + "$A1:D51]",db);
    while (query.next())
    {
        QList<QString> tempList = {};
        QString column0= query.value(0).toString();
        //qDebug() << "ID:" << column0;
        QString column1= query.value(1).toString();
        //qDebug() << "Otázka:" << column1;
        QString column2= query.value(2).toString();
        //qDebug() << "Odpověd:" << column2;
        QString column3= query.value(3).toString();
        //qDebug() << "Was question used:" << column3;
        tempList.append(column0);
        tempList.append(column1);
        tempList.append(column2);
        tempList.append(column3);
        list.append(tempList);
    }

    QSqlQuery query1("select * from [" + QString("Sheet1") + "$I1:L51]",db);
    while (query1.next())
    {
        QList<QString> tempList = {};
        QString column0= query1.value(0).toString();
        //qDebug() << "ID:" << column0;
        QString column1= query1.value(1).toString();
        //qDebug() << "Otázka:" << column1;
        QString column2= query1.value(2).toString();
        //qDebug() << "Odpověd:" << column2;
        QString column3= query1.value(3).toString();
        //qDebug() << "Was question used:" << column3;
        tempList.append(column0);
        tempList.append(column1);
        tempList.append(column2);
        tempList.append(column3);
        listgrey.append(tempList);
    }

    QString status = QString("Nahrávám otázky");
    QMessageBox::information(this, tr("Info"), status);

    excel = 1;
}

