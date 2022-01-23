#ifndef GREYQUESTION_H
#define GREYQUESTION_H

#include <QDialog>
#include <QTimeLine>
namespace Ui {
class GreyQuestion;
}

class GreyQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit GreyQuestion(QWidget *parent = nullptr);
    QString expected = "";
    QTimeLine *timeLine = new QTimeLine(1000, this);
    int questionID = 0;
    ~GreyQuestion();

private slots:
    void on_pushButtonAno_clicked();
    void time_out();
    void on_pushButtonNe_clicked();

private:
    Ui::GreyQuestion *ui;
};

#endif // GREYQUESTION_H
