#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>

const double PI=3.14159269;
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),kind(1)
{
    ui->setupUi(this);
    this->on_randCurve_clicked(true);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(this->width()/2,this->height()/2);
    painter.drawLine(this->width()/-2,0,this->width()/2,0);
    painter.drawLine(0,this->height()/-2,0,this->height()/2);
    painter.setPen(QPen(QColor(80,80,80),2));
    QList<QPointF> Points=this->getPoints(kind);
    for(int i=0;i<Points.size();i++)
    {
        painter.drawEllipse(Points[i].x()-5,Points[i].y()-5,10,10);
    }
    if(ui->chkbox->isChecked())
    {
        SmoothCurveCreator curve(Points);
        painter.drawPath(curve.path);
    }
    else
    {
        for(int i=1;i<Points.size();i++)
        {
            painter.drawLine(Points[i-1],Points[i]);
        }
    }
}

QList<QPointF> MainWidget::getPoints(int vari)
{
    QList<QPointF> points;
    int n=this->width()/100;
    int x=this->width()/-2;
    int dirta=5;
    switch(vari)
    {
        case 1:
            return randp;
            break;
        case 2:

            for(int i=1;i<=n;i++)
            {
                points.append(QPointF(x,this->width()/4*sin((i-1)*PI/2)));
                x+=100;
            }
            return points;
            break;
        case 3:
            n=this->width()/30;
            x=1;

            for(int i=1;i<=n;i++)
            {
                points.append(QPointF(x,-1*log(x/50.0)*50));
                x+=(10+dirta);
                dirta+=10;
            }
            return points;
            break;
         case 4:
            n=this->width()/100;
            x=this->width()/-2;
            for(int i=1;i<=n;i++)
            {
                points.append(QPointF(x,-1*pow(2.732,(i*100-this->width()/2)/100.0)*50));
                x+=100;
            }
            return points;
    }
    return randp;
}

void MainWidget::on_randCurve_clicked(bool checked)
{
    if(checked)
    {
        int n=this->width()/50;
        srand(time(NULL));
        randp.clear();
        randp.reserve(n);
        int x=this->width()/-2;
        for(int i=1;i<=n;i++)
        {
            randp.append(QPointF(x,(rand()%(this->width()/4))*(rand()%2==0?1:-1)));
            x+=50;
        }
        kind=1;
        this->update();
    }
}

void MainWidget::on_SinCurve_clicked(bool checked)
{
    if(checked)
        kind=2,this->update();
}

void MainWidget::on_lnCurve_clicked(bool checked)
{
    if(checked)
        kind=3,this->update();
}

void MainWidget::on_exCurve_clicked(bool checked)
{
    if(checked)
        kind=4,this->update();
}

void MainWidget::on_chkbox_clicked(bool checked)
{
    if(checked)
    {

    }
    else
    {

    }
    this->update();
}
