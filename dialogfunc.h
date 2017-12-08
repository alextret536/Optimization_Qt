#ifndef DIALOGFUNC_H
#define DIALOGFUNC_H

#include <QDialog>
#include"function.h"

namespace Ui {
class DialogFunc;
}

class DialogFunc : public QDialog
{
    Q_OBJECT
Function* F;
public:
    explicit DialogFunc(QWidget *parent = 0);
    Function* GetFunc();
    //int count;
    ~DialogFunc();

private slots:
  //  void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogFunc *ui;
};

#endif // DIALOGFUNC_H
