#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include<qimage.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;


//该类用来预处理图像
class preprocessor
{
   // Q_OBJECT
public:

    preprocessor(QString s);

    QImage main_process();

private:
    QImage M2Q(Mat);

    Mat Q2M(QString s);

    Mat flood_process();

    Mat imageSrc;
};

#endif // PREPROCESSOR_H
