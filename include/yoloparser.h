#ifndef YOLOPARSER_H
#define YOLOPARSER_H
#include"datatype.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <logging.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<vector>
#include "time.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "yolov5_lib.h"
#include <QObject>
#include"config.h"
using namespace cv;
//目标：
//通过parser来实时检测摄像头（视频源）如果出现了食物后 则开始进行录制并进行ROI检测（清晰度）如果达到阈值后则提取出来
//"E:\Tools\Yolov5\yolov5\weights\yolov5s6.wts"
class YOLOParser :public QObject {
    Q_OBJECT
public:
    YOLOParser() = default; // 添加默认构造函数
    YOLOParser(String, String);
    //YOLOParser(const YOLOParser&) = delete;
    //YOLOParser& operator=(const YOLOParser&) = delete;
    //~YOLOParser();
    //如果检测到了 则会对ROI区域进行录制

     // detect and show
    void TrtDetect();
    void showDetection(cv::Mat& img, std::vector<DetectBox>& boxes);
private:
    //需要储存的变量：模型路径
    String engine_path;
    String media_path;
    std::vector<DetectBox> det;
    float conf_thresh = kNmsThresh;
    void* trt_engine = NULL;
    cv::VideoWriter outputVideo;

};

#endif // YOLOPARSER_H
