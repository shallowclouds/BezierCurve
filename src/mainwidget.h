#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <SmoothCurveCreator.h>
#include <ctime>
#include <cstdlib>
#include <cmath>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_randCurve_clicked(bool checked);

    void on_SinCurve_clicked(bool checked);

    void on_lnCurve_clicked(bool checked);

    void on_exCurve_clicked(bool checked);

    void on_chkbox_clicked(bool checked);

private:
    Ui::MainWidget *ui;
    void paintEvent(QPaintEvent *);
    QList<QPointF> getPoints(int vari);
    int kind;
    QList<QPointF> randp;
};

#endif // MAINWIDGET_H
