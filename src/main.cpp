#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<YOLOParser>("YOLOParser");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
