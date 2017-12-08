#include "mainwindow.h"
#include <QApplication>

#include <QtGui>

class myWidget : public QWidget
{
    public:
        myWidget (QWidget *parent=0) : QWidget(parent)
        {
        }

        void paintEvent(QPaintEvent *pe)
        {    QPainter p(this);
             // тут и только тут должны быть все Ваши "рисования"
             p.drawLine(0,0,100,100);
        }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //myWidget w;
    MainWindow w;
    w.show();

    return a.exec();
}
