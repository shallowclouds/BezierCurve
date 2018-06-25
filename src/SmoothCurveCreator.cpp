#include "SmoothCurveCreator.h"

SmoothCurveCreator::SmoothCurveCreator(QList<QPointF> knots)//消元求解
{
    int n=knots.size()-1;
    QPointF rsp[n];
    for(int i=1;i<=n-2;i++)
    {
        rsp[i].setX(4*knots[i].x()+2*knots[i+1].x());
        rsp[i].setY(4*knots[i].y()+2*knots[i+1].y());
    }
    rsp[0].setX(knots[0].x()+2*knots[1].x());
    rsp[0].setY(knots[0].y()+2*knots[1].y());
    rsp[n-1].setX( ( 8*knots[n-1].x()+knots[n].x() )/2.0 );
    rsp[n-1].setY( ( 8*knots[n-1].y()+knots[n].y() )/2.0 );

    QPointF internal[n];
    QPointF temp[n];

    double b1=2.0,b2=2.0;
    internal[0].setX(rsp[0].x()/b1);
    internal[0].setY(rsp[0].y()/b2);
    for(int i=1;i<n;i++)
    {
        temp[i].setX(1/b1);
        temp[i].setY(1/b2);
        b1=(i<n-1?4.0:3.5)-temp[i].x();
        b2=(i<n-1?4.0:3.5)-temp[i].y();

        internal[i].setX((rsp[i].x()-internal[i-1].x())/b1);
        internal[i].setY((rsp[i].y()-internal[i-1].y())/b2);
    }
    for(int i=1;i<n;i++)
    {
        internal[n-i-1].setX(internal[n-i-1].x()-temp[n-i].x()*internal[n-i].x());
        internal[n-i-1].setY(internal[n-i-1].y()-temp[n-i].y()*internal[n-i].y());
    }
    ctrlPoint1.reserve(n);
    ctrlPoint2.reserve(n);
    for (int i=0;i<n;i++)
    {
        ctrlPoint1.append(internal[i]);
        if(i<n - 1)
           ctrlPoint2.append(QPointF(2*knots
                                          [i+1].x()-internal[i+1].x(),2*
                   knots[i+1].y()-internal[i+1].y()));
        else
           ctrlPoint2.append(QPointF((knots
                                           [n].x()+internal[n-1].x())/2,
                   (knots[n].y()+internal[n-1].y())/2));
    }
    this->path.moveTo(knots[0]);
    for(int i=0;i<n;i++)
    {
        this->path.cubicTo(ctrlPoint1[i],ctrlPoint2[i],knots[i+1]);
    }
}
