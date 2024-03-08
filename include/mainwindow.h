#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFileDialog>
#include<QProcess>
#include<QFile>
#include<QDebug>
#include<QGraphicsView>
#include<qgraphicsitem.h>
#include<QErrorMessage>
#include<QRect>
#include<QGraphicsView>
#include"preprocessor.h"
#include "yoloparser.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  //  Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage preProcess(QString);

private slots:
    void findImage();
    void runPython();


private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
