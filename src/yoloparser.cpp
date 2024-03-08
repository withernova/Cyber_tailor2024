#include "yoloparser.h"



YOLOParser::YOLOParser(String mpath,String mediapath):model_path(mpath),media_path(mediapath){
    trt_engine = yolov5_trt_create(model_path.c_str());
    printf("create yolov5-trt , instance = %p\n", trt_engine);
    std::string videopath = "saved.avi";
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    outputVideo.open(videopath,codec,25.0,cv::Size(1024, 576),true);
}
void YOLOParser::TrtDetect(){
    VideoCapture capture;
    bool isopen = capture.open(media_path);
    cv::Mat frame;
    while(capture.read(frame)){
        auto ret = yolov5_trt_detect(trt_engine, frame, conf_thresh,det);
        if(ret!= NULL){
            showDetection(frame,det);
        }
    }
}
void YOLOParser::showDetection(cv::Mat& img, std::vector<DetectBox>& boxes){
    cv::Mat temp = img.clone();
    //cv::imshow("img", temp);
    for (auto box : boxes) {
        cv::Point lt(box.x1, box.y1);
        cv::Point br(box.x2, box.y2);
        cv::rectangle(temp, lt, br, cv::Scalar(255, 0, 0), 1);
        std::string lbl;

        if (((int)box.classID) == 0) lbl = cv::format("%s", "head");
        else  lbl = cv::format("%s", "helmet");
        cv::putText(temp, lbl, lt, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 255, 0));
    }
    //cv::imshow("img", temp);
    cv::resize(temp, temp, cv::Size(1024, 576), 0, 0);
    outputVideo.write(temp);
    cv::waitKey(1);
}
