#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "dialogfunc.h"
#include <QPainter>
#include <QPen>
#include<QMouseEvent>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    eps=1e-3; delta=1e-8; method=1; stop=1;
   MainWindow::makePlot();
  // connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Dialog* Param = new Dialog(this);
     Param->show();
     Param->exec();
       opt=Param->GetOpt();
   //   makePlot();
}

void MainWindow::on_pushButton_2_clicked()
{
    DialogFunc* funParam = new DialogFunc(this);
     funParam->show();
     funParam->exec();
       F=funParam->GetFunc();
  //  DialogFunc dialogfunc;
   // dialogfunc.setModal(true);
makePlot();
}

void MainWindow:: makePlot()
{
 if (c1!=1) {F=new F1;};
    QCPAbstractPlottable* a=0;
  //  ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
     ui->customPlot->axisRect()->setupFullAxesBox(true);
     ui->customPlot->xAxis->setLabel("x");
     ui->customPlot->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap( ui->customPlot->xAxis,  ui->customPlot->yAxis);
    int nx = 700;
    int ny = 700;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(-5, 8), QCPRange(-5, 8)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
       // double r = 3*qSqrt(x*x+y*y)+1e-2;
          vector<double> arg(2);
          arg[0]=x; arg[1]=y;
          double r=F->f(arg);
       // z = 2*x*(qCos(r+2)/r-qSin(r+2)/r); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, r);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
    ui-> customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
     colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
     colorMap->setColorScale(colorScale); // associate the color map with the color scale
     colorScale->axis()->setLabel("Color Scale");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpCold);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
     ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
     ui->customPlot->rescaleAxes();
   connect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
}

void MainWindow::mousePress(QMouseEvent* mouse)
{

int xx=mouse->x();
int yy=mouse->y();
double xinPlot=ui->customPlot->xAxis->pixelToCoord(xx);
double yinPlot=ui->customPlot->yAxis->pixelToCoord(yy);x0={0,0};

//check

    x0[0]=xinPlot; x0[1]=yinPlot;
   // opt=new PolakRibiere();
    switch (method) {
    case 1:
        opt=new PolakRibiere(); break;
    case 2:
        opt=new RandomSearch(0.7); break;
    }
    switch (stop) {
    case 1:
       stopcriterion=new GradientNorm(); break;
    case 2:
       stopcriterion=new NumberOfIterations(); break;
    }
  //opt=new RandomSearch(0.7);
// stopcriterion=new GradientNorm();
  // stopcriterion=new NumberOfIterations();
    int dim=2;
    vector<double> l(dim);
    vector<double> r(dim);
    for (int i = 0; i < dim; i++) { l[i] = -5; r[i] = 8; }
    Area* Ar = new Area1(l,r);
   // double eps = 1e-3, delta = 1e-8, maxiter = 20000, maxiter_s = 10000;
     double maxiter = 20000, maxiter_s = 10000;
    Constant par(eps, delta, maxiter, maxiter_s);
   vector<double> res= opt->minimize(F,Ar,stopcriterion,x0,par);
   double result=F->f(res);
   QString str_result = QString::number(result);
   ui->label_2->setText(str_result);
   int iterations=path.size();
   QString str_iterations = QString::number(iterations-1);
   ui->label_4->setText(str_iterations);
     path=opt->GetPoints();
     QString x0x = QString::number(res[0]);
     ui->label_6->setText(x0x);
     QString x0y = QString::number(res[1]);
     ui->label_7->setText(x0y);

ui->customPlot->removePlottable(a);

 QCPCurve *TrajLine = new QCPCurve( ui->customPlot->xAxis,  ui->customPlot->yAxis);
      // generate the curve data points:
      const int pointCount = path.size();
      QVector<QCPCurveData> dataSpiral1(pointCount);
      for (int i=0; i<pointCount; ++i)
      {
        dataSpiral1[i] = QCPCurveData(i, path[i][0],(path[i][1]));
      }
      TrajLine->setPen(QPen(Qt::white));
      TrajLine->data()->set(dataSpiral1, true);
     // TrajLine->setScatterStyle((QCPScatterStyle(QCPScatterStyle::ssDisc , 2)));
ui->customPlot->replot();
 a=TrajLine;
}



void MainWindow::on_actionParameters_triggered()
{
    Dialog* Param = new Dialog(this);
     Param->show();
     Param->exec();
       opt=Param->GetOpt();
       method=Param->GetMeth();
      //c2=1;
     // makePlot();
}

void MainWindow::on_actionFunction_triggered()
{
    DialogFunc* funParam = new DialogFunc(this);
     funParam->show();
     funParam->exec();
       F=funParam->GetFunc();
      c1=1;
  //  DialogFunc dialogfunc;
   // dialogfunc.setModal(true);
makePlot();
}
