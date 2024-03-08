/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *SDType;
    QWidget *txt2img;
    QWidget *horizontalLayoutWidget_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QPushButton *submitBtn_t2i;
    QLineEdit *lineEdit_2;
    QLineEdit *step_t2i;
    QGraphicsView *outputPlace_t2i;
    QPlainTextEdit *prompt_t2i;
    QWidget *img2img;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *prompt_i2i;
    QHBoxLayout *fileBrowserLayout;
    QLineEdit *fileName_i2i;
    QPushButton *browseBtn_i2i;
    QPushButton *submitBtn_i2i;
    QGraphicsView *outputPlace_i2i;
    QHBoxLayout *stepLayout;
    QLineEdit *step_t2i_2;
    QSpacerItem *horizontalSpacer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        SDType = new QTabWidget(centralwidget);
        SDType->setObjectName("SDType");
        SDType->setGeometry(QRect(0, 0, 801, 671));
        SDType->setTabPosition(QTabWidget::North);
        SDType->setTabShape(QTabWidget::Rounded);
        SDType->setTabsClosable(false);
        SDType->setMovable(false);
        SDType->setTabBarAutoHide(false);
        txt2img = new QWidget();
        txt2img->setObjectName("txt2img");
        horizontalLayoutWidget_2 = new QWidget(txt2img);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 40, 781, 511));
        gridLayout = new QGridLayout(horizontalLayoutWidget_2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 5, 0, 1, 1);

        submitBtn_t2i = new QPushButton(horizontalLayoutWidget_2);
        submitBtn_t2i->setObjectName("submitBtn_t2i");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(submitBtn_t2i->sizePolicy().hasHeightForWidth());
        submitBtn_t2i->setSizePolicy(sizePolicy);

        gridLayout->addWidget(submitBtn_t2i, 6, 0, 1, 1);

        lineEdit_2 = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout->addWidget(lineEdit_2, 4, 0, 1, 1);

        step_t2i = new QLineEdit(horizontalLayoutWidget_2);
        step_t2i->setObjectName("step_t2i");

        gridLayout->addWidget(step_t2i, 3, 0, 1, 1);

        outputPlace_t2i = new QGraphicsView(horizontalLayoutWidget_2);
        outputPlace_t2i->setObjectName("outputPlace_t2i");

        gridLayout->addWidget(outputPlace_t2i, 0, 6, 7, 1);

        prompt_t2i = new QPlainTextEdit(horizontalLayoutWidget_2);
        prompt_t2i->setObjectName("prompt_t2i");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(prompt_t2i->sizePolicy().hasHeightForWidth());
        prompt_t2i->setSizePolicy(sizePolicy1);
        prompt_t2i->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(prompt_t2i, 0, 0, 3, 1);

        SDType->addTab(txt2img, QString());
        img2img = new QWidget();
        img2img->setObjectName("img2img");
        gridLayoutWidget = new QWidget(img2img);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 20, 751, 481));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        prompt_i2i = new QPlainTextEdit(gridLayoutWidget);
        prompt_i2i->setObjectName("prompt_i2i");
        sizePolicy1.setHeightForWidth(prompt_i2i->sizePolicy().hasHeightForWidth());
        prompt_i2i->setSizePolicy(sizePolicy1);
        prompt_i2i->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(prompt_i2i, 1, 0, 1, 1);

        fileBrowserLayout = new QHBoxLayout();
        fileBrowserLayout->setObjectName("fileBrowserLayout");
        fileName_i2i = new QLineEdit(gridLayoutWidget);
        fileName_i2i->setObjectName("fileName_i2i");

        fileBrowserLayout->addWidget(fileName_i2i);

        browseBtn_i2i = new QPushButton(gridLayoutWidget);
        browseBtn_i2i->setObjectName("browseBtn_i2i");

        fileBrowserLayout->addWidget(browseBtn_i2i);


        gridLayout_2->addLayout(fileBrowserLayout, 5, 0, 1, 1);

        submitBtn_i2i = new QPushButton(gridLayoutWidget);
        submitBtn_i2i->setObjectName("submitBtn_i2i");

        gridLayout_2->addWidget(submitBtn_i2i, 8, 0, 1, 1);

        outputPlace_i2i = new QGraphicsView(gridLayoutWidget);
        outputPlace_i2i->setObjectName("outputPlace_i2i");

        gridLayout_2->addWidget(outputPlace_i2i, 0, 1, 9, 1);

        stepLayout = new QHBoxLayout();
        stepLayout->setObjectName("stepLayout");
        step_t2i_2 = new QLineEdit(gridLayoutWidget);
        step_t2i_2->setObjectName("step_t2i_2");

        stepLayout->addWidget(step_t2i_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        stepLayout->addItem(horizontalSpacer);


        gridLayout_2->addLayout(stepLayout, 4, 0, 1, 1);

        SDType->addTab(img2img, QString());
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        SDType->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        submitBtn_t2i->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244", nullptr));
        prompt_t2i->setPlainText(QString());
        prompt_t2i->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204prompt\342\200\246\342\200\246", nullptr));
        SDType->setTabText(SDType->indexOf(txt2img), QCoreApplication::translate("MainWindow", "txt2img", nullptr));
        prompt_i2i->setPlainText(QString());
        prompt_i2i->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204prompt\342\200\246\342\200\246", nullptr));
        browseBtn_i2i->setText(QCoreApplication::translate("MainWindow", "\345\233\276\347\211\207\346\265\217\350\247\210", nullptr));
        submitBtn_i2i->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244", nullptr));
        step_t2i_2->setText(QString());
        SDType->setTabText(SDType->indexOf(img2img), QCoreApplication::translate("MainWindow", "img2img", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
