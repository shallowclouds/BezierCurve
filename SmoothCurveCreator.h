#ifndef SMOOTHCURVECREATOR_H
#define SMOOTHCURVECREATOR_H
#include <QList>
#include <QPainter>

class SmoothCurveCreator
{
public:
    SmoothCurveCreator(QList<QPointF> knots);
    QList<QPointF> ctrlPoint1,ctrlPoint2;
    QPainterPath path;
};

#endif // SMOOTHCURVECREATOR_H
