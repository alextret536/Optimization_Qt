#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
   // Opt=new PolakRibiere();
    QDoubleValidator* validator =  new QDoubleValidator( 0.0, 1.0,5,this );
       validator->setNotation( QDoubleValidator::ScientificNotation );
       ui->lineEdit->setValidator( validator );
       ui-> lineEdit_3->setValidator( new QIntValidator( 0, 1000000 ) );
       ui-> lineEdit_4->setValidator( new QIntValidator( 0, 1000000) );
 }

Dialog::~Dialog()
{
    delete ui;
}
Optimization* Dialog::GetOpt(){
    return Opt;
}
StopCriterion* Dialog::GetStopcriterion(){
    return stopcriterion;
}
double Dialog::GetEps(){
    return eps;
}
double Dialog::GetDelta(){
    return delta;
}
int Dialog::GetMeth(){
    return meth;
}
int Dialog::GetStop(){
    return stop;
}
void Dialog::on_buttonBox_accepted()
{
    if(ui->radioButton->isChecked()){
         // Opt=new PolakRibiere();
          meth=1;
    } else
    if(ui->radioButton_2->isChecked()){
        // Opt=new RandomSearch(0.7);
         meth=2;
    };
    if(ui->radioButton_3->isChecked()){
          stop=1;
    } else
    if(ui->radioButton_4->isChecked()){
         stop=2;
    };
    //bool ok;
 //   eps= ui->lineEdit->text().toDouble(&ok);
   // eps = ui->lineEdit->text().toDouble();
//     while (!ok) {
//      QMessageBox::information(this,"Error!","Input eps");
//      eps = ui->lineEdit->text().toDouble(&ok);
//}
     eps=ui->lineEdit->text().toDouble();
     delta = ui->lineEdit_2->text().toDouble();

}
//void Dialog::OKEnabled(){
//    ui->pushButton->setEnabled(ui->lineEdit->hasAcceptableInput());
//}

void Dialog::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked()){
         // Opt=new PolakRibiere();
          meth=1;
    } else
    if(ui->radioButton_2->isChecked()){
        // Opt=new RandomSearch(0.7);
         meth=2;
    };
    if(ui->radioButton_3->isChecked()){
          stop=1;
    } else
    if(ui->radioButton_4->isChecked()){
         stop=2;
    };
    //bool ok;
 //   eps= ui->lineEdit->text().toDouble(&ok);
   // eps = ui->lineEdit->text().toDouble();
//     while (!ok) {
//      QMessageBox::information(this,"Error!","Input eps");
//      eps = ui->lineEdit->text().toDouble(&ok);
//}
     eps=ui->lineEdit->text().toDouble();
     delta = ui->lineEdit_2->text().toDouble();

}
