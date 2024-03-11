#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    //qRegisterMetaType<MainWindow>("mainwindow");

    YOLOParser parser("E:/Tools/Yolov5/tensorrtx/yolov5/build/Debug/yolov5s.engine", "E:/Project/CreateAndInnovation/QtScripts/Cyber_tailor2024/Resources/e6ae67469df4936e2a1540e885b8d8b8.mp4");
    parser.TrtDetect();

    ui->setupUi(this);

    connect(ui->browseBtn_i2i,SIGNAL(clicked()),this,SLOT(findImage()));
    connect(ui->submitBtn_t2i,SIGNAL(clicked()),this,SLOT(runPython()));

}

MainWindow::~MainWindow(){
    delete ui;
}

QImage MainWindow::preProcess(QString src){
    preprocessor* processor = new preprocessor(src);
    return processor->main_process();
}

void MainWindow::findImage(){
    QString str = QFileDialog::getOpenFileName(this,"文件浏览","/","Image(*.png *.jpg;;All file(*.*)");
    ui->fileName_i2i->setText(str.toUtf8());
}

//启动python脚本
void MainWindow::runPython(){
    QWidget* tab = ui->SDType->currentWidget();
    QGraphicsView* outputPlace = tab->findChild<QGraphicsView*>();
    QString prompts = tab->findChild<QPlainTextEdit*>()->toPlainText();
    QString steps;
    QString imageData;
    QList<QLineEdit*> lines = tab->findChildren<QLineEdit*>();
    for(auto* item : lines){
        if(item->objectName().startsWith("step")){
            steps = item->text();
        }
        if(item->objectName().startsWith("fileName")){
            QString tmp = item->text();
          //  imageData = QImage(tmp).loadFromData(QByteArray::fromBase64())
            //将Qimage转换成字符串储存
        }
    }


    QProcess* process = new QProcess();
    process->setProgram("python");
    QStringList arguments;
    arguments << "../ImageProcessor/trial.py" << prompts<< steps;
    //qDebug()<<prompts<<steps;

    process->setArguments(arguments);

    QObject::connect(process, &QProcess::readyReadStandardOutput, [&]() {
        QByteArray output = process->readAllStandardOutput();

        output.remove(0,2);
        output.chop(4);

        QString result = QString::fromUtf8(output);
        QPixmap image;
        image.loadFromData(QByteArray::fromBase64(result.toLocal8Bit()), "PNG");
        qDebug()<<prompts<<steps;
        if (!image.isNull()){
            QPixmap imageProcessed = image.scaled(outputPlace->size().width(), outputPlace->size().height());
            QGraphicsScene* scene = new QGraphicsScene();
            scene->addPixmap(imageProcessed);
            scene->setSceneRect(imageProcessed.rect());
            outputPlace->setSceneRect(imageProcessed.rect());
            outputPlace->setScene(scene);
        }
    });

    process->start(); // 启动进程
    process->waitForFinished(-1);
    process->close();

}
