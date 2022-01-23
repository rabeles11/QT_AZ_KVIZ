#include "questionwindow.h"
#include "ui_questionwindow.h"
#include "QMessageBox"
#include "mainwindow.h"
#include "QTimeLine"
#include <iostream>
#include <QSqlQuery>
#include <QtSql/QSqlError>
#include <qprogressbar.h>
using namespace std;

QuestionWindow::QuestionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    //QTimeLine *timeLine = new QTimeLine(1000, this);
    timeLine->setDuration(10000);
    timeLine->setFrameRange(0, 100);
    timeLine->setEndFrame(100);
    connect(timeLine, &QTimeLine::frameChanged, ui->progressBar, &QProgressBar::setValue);


    connect(timeLine,&QTimeLine::finished,[this]() {
        cout << "Dopočítalo se!!" << endl;
        time_out();});

    timeLine->start();

    MainWindow * mw = MainWindow::getMainWinPtr();
    if(mw->excel == 1){
        srand(time(NULL));
        int number = rand() % 49;
        while(true){
            number = rand() % 49;
            cout << number << endl;
            if(mw->list[number][3].toInt() == 0){
                qDebug() << "Tuto už sem měl";
                break;
            }
        }
        ui->QuestionLabel->setText(mw->list[number][1]);
        expected = mw->list[number][2].toLower();
        qDebug() << mw->list[number];
        mw->list[number][3] = QString("1");
    }
    else{
        QSqlQuery query;
        QString sqlSelect = "SELECT * FROM QuestionMainGame WHERE WasQuestionUsed=1 ORDER BY random() LIMIT 1";
        query.exec(sqlSelect);

        if(query.lastError().isValid()){
                qWarning() << "SELECT" << query.lastError().text();
            }
        while(query.next()){
            QString Question = query.value("Question").toString();
            QString QuestionExpected = query.value("Expected_reply").toString().toLower();
            questionID = query.value("id").toInt();
            ui->QuestionLabel->setText(Question);
            expected = QuestionExpected;
        }
        // updating Data
         query.prepare("UPDATE QuestionMainGame SET WasQuestionUsed=0 WHERE id=(:id)");
         query.bindValue(0,questionID);
         query.exec();
    }


    //ui->QuestionLabel->setText("Jak se jmenuje tato lod ?");
}

QuestionWindow::~QuestionWindow()
{
    delete ui;
}

void SwapPlayer2(){
    MainWindow * mw = MainWindow::getMainWinPtr();
    if(mw->Player1.is_on_turn){
        mw->Player2.is_on_turn = true;
        mw->Player1.is_on_turn = false;
    }
    else{
        mw->Player2.is_on_turn = false;
        mw->Player1.is_on_turn = true;
    }
}

void QuestionWindow::on_pushButton_clicked()
{

    if(ui->plainTextEditReply->toPlainText().isEmpty()){
        QMessageBox::information(
            this,
            tr("AZKvíz"),
            tr("Pozor máš prázdné pole!!") );
    }
    else if(ui->plainTextEditReply->toPlainText().toLower() == expected)
    {
        MainWindow * mw = MainWindow::getMainWinPtr();
        if(mw->Player1.is_on_turn){
           mw->Player1.PositiveReply += 1;
           mw->Player1.buttonList.append(mw->buttonss->objectName());
           mw->p1.append(mw->buttonss);
           //mw->Player1.test.append(mw->buttonss);
           // tady začíná hlídání hranic
           if(mw->buttonss->toolTip() == "Left"){
               mw->Player1.left = true;
           }
           else if(mw->buttonss->toolTip() == "Left and Right"){
               mw->Player1.left = true;
               mw->Player1.right = true;
           }
           else if(mw->buttonss->toolTip() == "Left and Bottom"){
               mw->Player1.left = true;
               mw->Player1.bottom = true;
           }
           else if(mw->buttonss->toolTip() == "Right"){
               mw->Player1.right = true;
           }
           else if(mw->buttonss->toolTip() == "Right and Bottom"){
               mw->Player1.right = true;
               mw->Player1.bottom = true;
           }
           else if(mw->buttonss->toolTip() == "Bottom"){
               mw->Player1.bottom = true;
           }

           // tady končí hlídání hranic


           mw->pbSetColorGreen();

        }
        else{
            mw->Player2.PositiveReply += 1;
            mw->Player2.buttonList.append(mw->buttonss->objectName());
            mw->p2.append(mw->buttonss);
            // tady začíná hlídání hranic
            if(mw->buttonss->toolTip() == "Left"){
                mw->Player2.left = true;
            }
            else if(mw->buttonss->toolTip() == "Left and Right"){
                mw->Player2.left = true;
                mw->Player2.right = true;
            }
            else if(mw->buttonss->toolTip() == "Left and Bottom"){
                mw->Player2.left = true;
                mw->Player2.bottom = true;
            }
            else if(mw->buttonss->toolTip() == "Right"){
                mw->Player2.right = true;
            }
            else if(mw->buttonss->toolTip() == "Right and Bottom"){
                mw->Player2.right = true;
                mw->Player2.bottom = true;
            }
            else if(mw->buttonss->toolTip() == "Bottom"){
                mw->Player2.bottom = true;
            }

            // tady končí hlídání hranic
            mw->pbSetColorRed();
        }
        SwapPlayer2();
        this->close();
        delete this;
    }
    else if (playerbadreply == 1 and didhereplyyet==true){
        MainWindow * mw = MainWindow::getMainWinPtr();
        if(ui->plainTextEditReply->toPlainText() == expected){
            if(mw->Player1.is_on_turn){
               mw->pbSetColorGreen();
               mw->Player1.PositiveReply +=1;
               mw->Player1.buttonList.append(mw->buttonss->objectName());
               mw->p1.append(mw->buttonss);
               // tady začíná hlídání hranic
               if(mw->buttonss->toolTip() == "Left"){
                   mw->Player1.left = true;
               }
               else if(mw->buttonss->toolTip() == "Left and Right"){
                   mw->Player1.left = true;
                   mw->Player1.right = true;
               }
               else if(mw->buttonss->toolTip() == "Left and Bottom"){
                   mw->Player1.left = true;
                   mw->Player1.bottom = true;
               }
               else if(mw->buttonss->toolTip() == "Right"){
                   mw->Player1.right = true;
               }
               else if(mw->buttonss->toolTip() == "Right and Bottom"){
                   mw->Player1.right = true;
                   mw->Player1.bottom = true;
               }
               else if(mw->buttonss->toolTip() == "Bottom"){
                   mw->Player1.bottom = true;
               }

               // tady končí hlídání hranic
            }
            else{
                mw->pbSetColorRed();
                mw->Player2.PositiveReply +=1;
                mw->Player2.buttonList.append(mw->buttonss->objectName());
                mw->p2.append(mw->buttonss);

                if(mw->buttonss->toolTip() == "Left"){
                    mw->Player2.left = true;
                }
                else if(mw->buttonss->toolTip() == "Left and Right"){
                    mw->Player2.left = true;
                    mw->Player2.right = true;
                }
                else if(mw->buttonss->toolTip() == "Left and Bottom"){
                    mw->Player2.left = true;
                    mw->Player2.bottom = true;
                }
                else if(mw->buttonss->toolTip() == "Right"){
                    mw->Player2.right = true;
                }
                else if(mw->buttonss->toolTip() == "Right and Bottom"){
                    mw->Player2.right = true;
                    mw->Player2.bottom = true;
                }
                else if(mw->buttonss->toolTip() == "Bottom"){
                    mw->Player2.bottom = true;
                }
            }
        }
        else
        {
            mw->pbSetColorGrey();
        }
        this->close();
        delete this;
    }
    else{
       ui->plainTextEditReply->clear();
       MainWindow * mw = MainWindow::getMainWinPtr();
       SwapPlayer2();
       timeLine->setPaused(true);
       QMessageBox::information(
           this,
           tr("AZKvíz"),
           tr("Odpověděl si špatně!!")
       );
       QMessageBox msgBox;
       msgBox.setWindowTitle("Pozor");
       msgBox.setText("Přeje si odpovědět další hráč?");
       msgBox.setStandardButtons(QMessageBox::Yes);
       msgBox.addButton(QMessageBox::No);
       msgBox.setDefaultButton(QMessageBox::No);
       if(msgBox.exec() == QMessageBox::Yes){
         didhereplyyet = true;
         playerbadreply = 1;
         cout << ui->progressBar->value() << endl;
         //ui->progressBar->setValue(0);
         timeLine->setPaused(true);  // takhle se resetuje
         timeLine->start();
         //ui->progressBar->reset();
       }else {

        /*
        QMessageBox::information(
               this,
               tr("AZKvíz"),
               tr("Odpověděl si špatně!!")
         );
         */
         mw->pbSetColorGrey();
         this->close();
         delete this;
       }
       //playerbadreply = 1;


       //mw->pbSetColorGrey();
       //this->close();
    }
}


void QuestionWindow::on_pushButton_DontKnowAnswer_clicked()
{

    MainWindow * mw = MainWindow::getMainWinPtr();
    timeLine->setPaused(true);
    QMessageBox msgBox;
    if(didhereplyyet == true){
        mw->pbSetColorGrey();
        this->close();
        delete this;
    }
    else{
        msgBox.setWindowTitle("Pozor");
        msgBox.setText("Přeje si odpovědět další hráč?");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
          playerbadreply = 1;
          SwapPlayer2();
          timeLine->setPaused(true);  // takhle se resetuje
          timeLine->start();
          didhereplyyet = true;
          //ui->progressBar->setValue(0);
          //ui->progressBar->reset();
        }else {
          mw->pbSetColorGrey();
          this->close();
          delete this;
        }
    }
}

void QuestionWindow::time_out(){
    MainWindow * mw = MainWindow::getMainWinPtr();
    QMessageBox msgBox;
    if(didhereplyyet == true){
        QMessageBox::information(
               this,
               tr("AZKvíz"),
               tr("Vypršel čas!!!!")
         );
        mw->pbSetColorGrey();
        this->close();
        delete this;
    }
    else{
        msgBox.setWindowTitle("Pozor");
        msgBox.setText("Vypřšel čas!! Přeje si odpovědět další hráč?");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
          playerbadreply = 1;
          SwapPlayer2();
          timeLine->setPaused(true);  // takhle se resetuje
          timeLine->start();
          didhereplyyet = true;
          //ui->progressBar->setValue(0);
          //ui->progressBar->reset();
        }else {
          SwapPlayer2();
          mw->pbSetColorGrey();
          this->close();
          delete this;
        }
    }

}

