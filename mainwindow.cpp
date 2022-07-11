#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include "model.h"

Model myModel;
void MainWindow::onTimerTicked(){

    if(myModel.isDataUpdated()){

        if(myModel.pointsQ.size()>500){
            myModel.pointsQ.dequeue();
        }
        myModel.pointsQ.enqueue({myModel.getX(),myModel.getY()});
    }
    update();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    timer = new QTimer();
    connect( timer, SIGNAL( timeout()),SLOT(onTimerTicked()));
    timer->setInterval(3);
    timer->start();

}


MainWindow::~MainWindow()
{


    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);


   int deltax = width()/2;
   int deltay = height()/2;
   QPen penCoords(Qt::green, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
   QPen pen(Qt::black,2);

   painter.setPen(penCoords);
   painter.drawLine(0,deltay,width(),deltay);
   painter.drawLine(deltax,0,deltax,height());

   painter.setPen(pen);



   for(auto i =0 ; i<myModel.pointsQ.size()-1;i++){
       int x1 = myModel.pointsQ[i].x();
       int y1 = myModel.pointsQ[i].y();
       int x2 = myModel.pointsQ[i+1].x();
       int y2 = myModel.pointsQ[i+1].y();
        painter.setPen(pen);
       painter.drawLine(x1+deltax, y1+deltay,x2+deltax, y2+deltay);
   }
   if(!myModel.pointsQ.isEmpty()){
       QPen penP(Qt::red,3);
       painter.setPen(penP);
       painter.drawEllipse(myModel.pointsQ.back().x()+deltax, myModel.pointsQ.back().y()+deltay,4,4);
   }


}

void MainWindow::on_doubleSpinBox_Ax_valueChanged(double arg1)
{
    myModel.setAx(arg1);
}

void MainWindow::on_doubleSpinBox_Wx_valueChanged(double arg1)
{
    myModel.setWx(arg1);
}

void MainWindow::on_doubleSpinBox_Dx_valueChanged(double arg1)
{
    myModel.setDx(arg1);
}

void MainWindow::on_doubleSpinBox_Ay_valueChanged(double arg1)
{
    myModel.setAy(arg1);
}

void MainWindow::on_doubleSpinBox_Wy_valueChanged(double arg1)
{
    myModel.setWy(arg1);
}

void MainWindow::on_doubleSpinBox_Dy_valueChanged(double arg1)
{
    myModel.setDy(arg1);
}

void MainWindow::on_pushButton_startX_clicked()
{
    myModel.StartThreadX();
    ui->pushButton_startX->setEnabled(false);
    ui->pushButton_stopX->setEnabled(true);
}

void MainWindow::on_pushButton_startY_clicked()
{
    myModel.StartThreadY();
    ui->pushButton_startY->setEnabled(false);
    ui->pushButton_stopY->setEnabled(true);

}

void MainWindow::on_pushButton_stopX_clicked()
{
    myModel.StopThreadX();
    ui->pushButton_startX->setEnabled(true);
    ui->pushButton_stopX->setEnabled(false);

}

void MainWindow::on_pushButton_stopY_clicked()
{
    myModel.StopThreadY();
    ui->pushButton_startY->setEnabled(true);
    ui->pushButton_stopY->setEnabled(false);
}

