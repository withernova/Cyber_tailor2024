
#pragma once 
#ifdef __cplusplus
#include "datatype.h"
extern "C" 
{
#endif 

//如manager类所说 该类函数被manager高度依赖 更接近yolo源码的底层 需要着重解读

//初始化构建模型 所以传入模型的路径
void * yolov5_trt_create(const char * engine_name);
 
 //传入检测目标 阈值 以及det（一一对应的检测方框 来源于datatype类
int yolov5_trt_detect(void *h, cv::Mat &img, float threshold,std::vector<DetectBox>& det);

//应该是析构吧
void yolov5_trt_destroy(void *h);
 
#ifdef __cplusplus
}
#endif 
