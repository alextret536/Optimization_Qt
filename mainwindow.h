#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"function.h"
#include"stopcriterion.h"
#include"optimization.h"
#include"area.h"
#include"const.h"
#include"qcustomplot.h"
#include<deque>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
Function* F;
vector<double> x0;
vector<vector<double> > path;
Optimization* opt;
StopCriterion* stopcriterion;
double eps,delta;
QCPAbstractPlottable* a;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
int c1,method,stop;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void makePlot();
    void on_actionParameters_triggered();

    void on_actionFunction_triggered();

public slots:
     void mousePress(QMouseEvent*);
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
