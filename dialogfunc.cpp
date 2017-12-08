#include "dialogfunc.h"
#include "ui_dialogfunc.h"
#include "function.h"
#include"mainwindow.h"

DialogFunc::DialogFunc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFunc)
{
    ui->setupUi(this);
    F=new F1();
}

DialogFunc::~DialogFunc()
{
    delete ui;
}
Function* DialogFunc::GetFunc() {
    return F;
}

void DialogFunc::on_buttonBox_accepted()
{
    if(ui->radioButton->isChecked()){
          F = new F1();
    } else
    if(ui->radioButton_2->isChecked()){
          F = new F2();
    }
    else
        if(ui->radioButton_3->isChecked()){
          F = new F3();
        };
//count=1;
}
