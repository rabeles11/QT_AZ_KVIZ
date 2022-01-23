#include "greyquestion.h"
#include "ui_greyquestion.h"
#include "mainwindow.h"
#include <iostream>
#include <QSqlQuery>
#include <QtSql/QSqlError>
using namespace std;

GreyQuestion::GreyQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GreyQuestion)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
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
            if(mw->listgrey[number][3].toInt() == 0){
                qDebug() << "Tuto už sem měl";
                break;
            }
        }
        ui->QuestionLabel->setText(mw->listgrey[number][1]);
        expected = mw->listgrey[number][2];
        qDebug() << mw->listgrey[number];
        mw->listgrey[number][3] = QString("1");
    }
    else{
        QSqlQuery query;
        QString sqlSelect = "SELECT * FROM QuestionsYesOrNot WHERE WasQuestionUsed=1 ORDER BY random() LIMIT 1";
        query.exec(sqlSelect);

        if(query.lastError().isValid()){
                qWarning() << "SELECT" << query.lastError().text();
            }
        while(query.next()){
            QString Question = query.value("Question").toString();
            QString QuestionExpected = query.value("Expected_reply").toString();
            questionID = query.value("id").toInt();
            ui->QuestionLabel->setText(Question);
            expected = QuestionExpected; // pořešit LowerCase
        }
        // updating Data
         query.prepare("UPDATE QuestionsYesOrNot SET WasQuestionUsed=0 WHERE id=(:id)");
         query.bindValue(0,questionID);
         query.exec();
    }

}

GreyQuestion::~GreyQuestion()
{
    delete ui;
}

void SwapPlayer(){
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

void GreyQuestion::on_pushButtonAno_clicked()
{
    MainWindow * mw = MainWindow::getMainWinPtr();
    if(ui->pushButtonAno->text()==expected){      //tady nastav potom jestli je odpověd ano kontroluj hráče!!
        if(mw->Player1.is_on_turn){
           mw->Player1.PositiveReply += 1;
           mw->pbSetColorGreen();
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
            mw->Player2.PositiveReply += 1;
            mw->pbSetColorRed();
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
        }
        SwapPlayer();
        this->close();
        delete this;
    }
    else{
        mw->pbSetColorGrey();
        SwapPlayer();
        this->close();
        delete this;
    }
}


void GreyQuestion::on_pushButtonNe_clicked()
{
    MainWindow * mw = MainWindow::getMainWinPtr();
    if(ui->pushButtonNe->text()==expected){      //tady nastav potom jestli je odpověd ano kontroluj hráče!!
        if(mw->Player1.is_on_turn){
           mw->Player1.PositiveReply += 1;
           mw->pbSetColorGreen();
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
            mw->Player2.PositiveReply += 1;
            mw->pbSetColorRed();
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
        }
        SwapPlayer();
        this->close();
        delete this;
    }
    else{
        mw->pbSetColorGrey();
        SwapPlayer();
        this->close();
        delete this;
    }

}

void GreyQuestion::time_out(){
    QMessageBox::information(
           this,
           tr("AZKvíz"),
           tr("Vypršel čas!!!!")
     );
    SwapPlayer();
    this->close();
    delete this;
}

