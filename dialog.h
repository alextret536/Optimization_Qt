#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "optimization.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
Optimization* Opt;
StopCriterion* stopcriterion;
double eps,delta;
int meth,stop;
public:
    explicit Dialog(QWidget *parent = 0);
Optimization* GetOpt();
StopCriterion* GetStopcriterion();
double GetEps();
double GetDelta();
int GetMeth();
int GetStop();
    ~Dialog();

private slots:
    void on_buttonBox_accepted();
    void  OKEnabled();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
