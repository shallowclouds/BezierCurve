#include "mainwidget.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Set application style for a modern look
    a.setStyle(QStyleFactory::create("Fusion"));
    
    MainWidget w;
    w.show();

    return a.exec();
}
