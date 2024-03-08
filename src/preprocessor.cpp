#include "../include/preprocessor.h"

preprocessor::preprocessor(QString s){

    this->imageSrc = Q2M(s);
}

QImage preprocessor::main_process(){
    Mat ret = flood_process();
    QImage image = M2Q(ret);
    return image;
}

Mat preprocessor::flood_process(){
    Mat ret = Mat::zeros(Size(imageSrc.cols+2 , imageSrc.rows+2),CV_8UC1);
    floodFill(imageSrc, ret, Point(50,50),Scalar(0,255,0));
    imshow("yee",ret);
    return ret;
}

Mat preprocessor::Q2M(QString s){
    // 假设已经加载了Qt QImage对象
    QImage src(s);

    QImage rgbImage = src.convertToFormat(QImage::Format_RGB888);
    // 将图像转换为RGB格式
    cv::Mat mat(src.height(), src.width(), CV_8UC3, (uchar*)rgbImage.bits(), rgbImage.bytesPerLine());

    return mat;
}

QImage preprocessor::M2Q(Mat src){
    QImage image(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_RGB888);
    // 返回 QImage
    return image;
}
