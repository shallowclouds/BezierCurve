#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <SmoothCurveCreator.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGestureEvent>
#include <QPinchGesture>
#include <QSwipeGesture>
#include <QTimer>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    
    qreal zoomFactor() const { return m_zoomFactor; }
    void setZoomFactor(qreal factor);

protected:
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_randCurve_clicked(bool checked);
    void on_SinCurve_clicked(bool checked);
    void on_lnCurve_clicked(bool checked);
    void on_exCurve_clicked(bool checked);
    void on_chkbox_clicked(bool checked);
    void on_themeCombo_currentIndexChanged(int index);
    void on_animateBtn_clicked();
    void on_resetZoomBtn_clicked();
    void updateAnimation();

private:
    Ui::MainWidget *ui;
    void paintEvent(QPaintEvent *);
    QList<QPointF> getPoints(int vari);
    bool gestureEvent(QGestureEvent *event);
    void pinchTriggered(QPinchGesture *gesture);
    void swipeTriggered(QSwipeGesture *gesture);
    void setupThemes();
    void applyTheme(int themeIndex);
    void setupResponsiveLayout();
    
    int kind;
    QList<QPointF> randp;
    qreal m_zoomFactor;
    QPropertyAnimation *curveAnimation;
    QTimer *animationTimer;
    int animationStep;
    bool isAnimating;
    QList<QColor> themeColors;
    QColor currentLineColor;
    QColor currentPointColor;
    QColor currentBackgroundColor;
};

#endif // MAINWIDGET_H
