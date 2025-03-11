#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QDebug>

const double PI=3.14159269;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    kind(1),
    m_zoomFactor(1.0),
    animationStep(0),
    isAnimating(false)
{
    ui->setupUi(this);
    
    // Enable gesture recognition
    grabGesture(Qt::PinchGesture);
    grabGesture(Qt::SwipeGesture);
    grabGesture(Qt::PanGesture);
    
    // Setup animation
    curveAnimation = new QPropertyAnimation(this, "zoomFactor");
    curveAnimation->setDuration(1000);
    curveAnimation->setStartValue(1.0);
    curveAnimation->setEndValue(1.5);
    curveAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    
    // Setup animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWidget::updateAnimation);
    
    // Setup themes
    setupThemes();
    applyTheme(0); // Default theme
    
    // Setup responsive layout
    setupResponsiveLayout();
    
    // Initialize with random curve
    this->on_randCurve_clicked(true);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete curveAnimation;
    delete animationTimer;
}

void MainWidget::setupThemes()
{
    // Define different color themes
    themeColors.append(QColor(80, 80, 80)); // Default gray
    themeColors.append(QColor(41, 128, 185)); // Blue
    themeColors.append(QColor(39, 174, 96)); // Green
    themeColors.append(QColor(192, 57, 43)); // Red
    themeColors.append(QColor(142, 68, 173)); // Purple
    
    // Set current colors
    currentLineColor = themeColors[0];
    currentPointColor = themeColors[0];
    currentBackgroundColor = QColor(255, 255, 255);
}

void MainWidget::applyTheme(int themeIndex)
{
    if (themeIndex < 0 || themeIndex >= themeColors.size())
        return;
        
    currentLineColor = themeColors[themeIndex];
    currentPointColor = themeColors[themeIndex];
    
    // Adjust background color based on theme
    switch(themeIndex) {
        case 0: // Default
            currentBackgroundColor = QColor(255, 255, 255);
            break;
        case 1: // Blue theme
            currentBackgroundColor = QColor(235, 245, 251);
            break;
        case 2: // Green theme
            currentBackgroundColor = QColor(235, 251, 242);
            break;
        case 3: // Red theme
            currentBackgroundColor = QColor(251, 235, 235);
            break;
        case 4: // Purple theme
            currentBackgroundColor = QColor(245, 235, 251);
            break;
    }
    
    // Apply background color
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, currentBackgroundColor);
    setPalette(pal);
    
    update();
}

void MainWidget::setupResponsiveLayout()
{
    // Make the widget responsive to screen size
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    
    int width = screenGeometry.width() * 0.8;
    int height = screenGeometry.height() * 0.8;
    
    resize(width, height);
    
    // Adjust UI elements based on screen size
    if (width < 600) {
        // Mobile layout
        ui->controlPanel->setGeometry(0, 0, width, 150);
    } else {
        // Desktop layout
        ui->controlPanel->setGeometry(0, 0, 200, height);
    }
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    
    // Adjust UI elements based on new size
    int width = event->size().width();
    int height = event->size().height();
    
    if (width < 600) {
        // Mobile layout
        ui->controlPanel->setGeometry(0, 0, width, 150);
    } else {
        // Desktop layout
        ui->controlPanel->setGeometry(0, 0, 200, height);
    }
}

bool MainWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QWidget::event(event);
}

bool MainWidget::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
        swipeTriggered(static_cast<QSwipeGesture *>(swipe));
    return true;
}

void MainWidget::pinchTriggered(QPinchGesture *gesture)
{
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        qreal scaleFactor = gesture->totalScaleFactor();
        setZoomFactor(scaleFactor);
    }
    update();
}

void MainWidget::swipeTriggered(QSwipeGesture *gesture)
{
    if (gesture->state() == Qt::GestureFinished) {
        if (gesture->horizontalDirection() == QSwipeGesture::Left) {
            // Next curve type
            int nextKind = (kind % 4) + 1;
            switch (nextKind) {
                case 1: ui->randCurve->click(); break;
                case 2: ui->SinCurve->click(); break;
                case 3: ui->lnCurve->click(); break;
                case 4: ui->exCurve->click(); break;
            }
        } else if (gesture->horizontalDirection() == QSwipeGesture::Right) {
            // Previous curve type
            int prevKind = (kind - 2 + 4) % 4 + 1;
            switch (prevKind) {
                case 1: ui->randCurve->click(); break;
                case 2: ui->SinCurve->click(); break;
                case 3: ui->lnCurve->click(); break;
                case 4: ui->exCurve->click(); break;
            }
        }
    }
}

void MainWidget::setZoomFactor(qreal factor)
{
    if (factor < 0.5)
        factor = 0.5;
    if (factor > 3.0)
        factor = 3.0;
    
    m_zoomFactor = factor;
    update();
}

void MainWidget::on_resetZoomBtn_clicked()
{
    setZoomFactor(1.0);
}

void MainWidget::on_animateBtn_clicked()
{
    if (isAnimating) {
        animationTimer->stop();
        isAnimating = false;
        ui->animateBtn->setText("动画");
    } else {
        animationStep = 0;
        animationTimer->start(50);
        isAnimating = true;
        ui->animateBtn->setText("停止");
    }
}

void MainWidget::updateAnimation()
{
    animationStep++;
    if (animationStep > 100) {
        animationStep = 0;
    }
    update();
}

void MainWidget::on_themeCombo_currentIndexChanged(int index)
{
    applyTheme(index);
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    
    // Fill background
    painter.fillRect(rect(), currentBackgroundColor);
    
    // Apply zoom factor
    painter.translate(this->width()/2, this->height()/2);
    painter.scale(m_zoomFactor, m_zoomFactor);
    
    // Draw coordinate axes
    painter.setPen(QPen(QColor(200, 200, 200), 1));
    painter.drawLine(this->width()/-2, 0, this->width()/2, 0);
    painter.drawLine(0, this->height()/-2, 0, this->height()/2);
    
    // Get points for current curve type
    QList<QPointF> Points = this->getPoints(kind);
    
    // Draw points
    painter.setPen(QPen(currentPointColor, 2));
    painter.setBrush(QBrush(currentPointColor.lighter(150)));
    
    for(int i=0; i<Points.size(); i++)
    {
        // Apply animation effect if animating
        QPointF point = Points[i];
        if (isAnimating) {
            // Add a subtle wave effect during animation
            qreal offset = sin(animationStep * 0.1 + i * 0.5) * 10;
            point.setY(point.y() + offset);
        }
        
        // Draw point with hover effect
        QRectF pointRect(point.x()-5, point.y()-5, 10, 10);
        painter.drawEllipse(pointRect);
    }
    
    // Draw curve or lines
    painter.setPen(QPen(currentLineColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    
    if(ui->chkbox->isChecked())
    {
        // Create smooth curve
        SmoothCurveCreator curve(Points);
        
        // Apply animation effect if animating
        if (isAnimating) {
            // Draw with gradient for animation effect
            QLinearGradient gradient(QPointF(-width()/2, 0), QPointF(width()/2, 0));
            qreal pos = (animationStep % 100) / 100.0;
            gradient.setColorAt((pos + 0.0) > 1.0 ? (pos - 1.0) : pos, currentLineColor);
            gradient.setColorAt((pos + 0.3) > 1.0 ? (pos - 0.7) : (pos + 0.3), currentLineColor.lighter(150));
            gradient.setColorAt((pos + 0.6) > 1.0 ? (pos - 0.4) : (pos + 0.6), currentLineColor);
            
            painter.setPen(QPen(QBrush(gradient), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        
        painter.drawPath(curve.path);
    }
    else
    {
        // Draw straight lines between points
        for(int i=1; i<Points.size(); i++)
        {
            QPointF p1 = Points[i-1];
            QPointF p2 = Points[i];
            
            // Apply animation effect if animating
            if (isAnimating) {
                qreal offset1 = sin(animationStep * 0.1 + (i-1) * 0.5) * 10;
                qreal offset2 = sin(animationStep * 0.1 + i * 0.5) * 10;
                p1.setY(p1.y() + offset1);
                p2.setY(p2.y() + offset2);
            }
            
            painter.drawLine(p1, p2);
        }
    }
}

QList<QPointF> MainWidget::getPoints(int vari)
{
    QList<QPointF> points;
    int n = this->width()/100;
    int x = this->width()/-2;
    int dirta = 5;
    
    switch(vari)
    {
        case 1:
            return randp;
            
        case 2:
            for(int i=1; i<=n; i++)
            {
                points.append(QPointF(x, this->width()/4*sin((i-1)*PI/2)));
                x += 100;
            }
            return points;
            
        case 3:
            n = this->width()/30;
            x = 1;

            for(int i=1; i<=n; i++)
            {
                points.append(QPointF(x, -1*log(x/50.0)*50));
                x += (10+dirta);
                dirta += 10;
            }
            return points;
            
        case 4:
            n = this->width()/100;
            x = this->width()/-2;
            for(int i=1; i<=n; i++)
            {
                points.append(QPointF(x, -1*pow(2.732, (i*100-this->width()/2)/100.0)*50));
                x += 100;
            }
            return points;
    }
    
    return randp;
}

void MainWidget::on_randCurve_clicked(bool checked)
{
    if(checked)
    {
        int n = this->width()/50;
        srand(time(NULL));
        randp.clear();
        randp.reserve(n);
        int x = this->width()/-2;
        
        for(int i=1; i<=n; i++)
        {
            randp.append(QPointF(x, (rand()%(this->width()/4))*(rand()%2==0?1:-1)));
            x += 50;
        }
        
        kind = 1;
        this->update();
    }
}

void MainWidget::on_SinCurve_clicked(bool checked)
{
    if(checked)
        kind = 2, this->update();
}

void MainWidget::on_lnCurve_clicked(bool checked)
{
    if(checked)
        kind = 3, this->update();
}

void MainWidget::on_exCurve_clicked(bool checked)
{
    if(checked)
        kind = 4, this->update();
}

void MainWidget::on_chkbox_clicked(bool checked)
{
    this->update();
}
