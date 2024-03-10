#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_ImageProcessor.h"
#include "ui_mainwindow.h"

class ImageProcessor : public QMainWindow {
	Q_OBJECT

public:
	ImageProcessor(QWidget* parent = nullptr);
	~ImageProcessor();

private:
	Ui::MainWindow ui;
};
