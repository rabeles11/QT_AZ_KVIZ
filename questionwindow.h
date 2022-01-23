#ifndef QUESTIONWINDOW_H
#define QUESTIONWINDOW_H

#include <QDialog>
#include "mainwindow.h"
#include "QTimeLine"
namespace Ui {
class QuestionWindow;
}

class QuestionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionWindow(QWidget *parent = nullptr);
    ~QuestionWindow();
    int playerbadreply = 0;
    QString expected = "";
    int questionID = 0;
    bool didhereplyyet = false;
    QString buttonName = "";
    QTimeLine *timeLine = new QTimeLine(1000, this);


private slots:
    void on_pushButton_clicked();
    void time_out();
    void on_pushButton_DontKnowAnswer_clicked();

private:
    Ui::QuestionWindow *ui;
};

#endif // QUESTIONWINDOW_H
