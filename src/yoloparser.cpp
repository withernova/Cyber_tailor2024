#include "yoloparser.h"



YOLOParser::YOLOParser(String mpath,String mediapath):engine_path(mpath),media_path(mediapath){
    trt_engine = yolov5_trt_create(engine_path.c_str());
    cv::VideoCapture cap(media_path);  // �滻Ϊ������Ƶ�ļ�·��
    // ��ȡ��Ƶ�Ŀ�Ⱥ͸߶�
    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    // �ǵ��ڽ���ʱ�ͷ�VideoCapture��Դ
    cap.release();
    output_cols = width;
    output_rows= height;

    printf("create yolov5-trt , instance = %p\n", trt_engine);
    std::string videopath = "saved.avi";
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    outputVideo.open(videopath,codec,25.0,cv::Size(output_cols, output_rows), true);
}
void YOLOParser::TrtDetect(){
    VideoCapture capture;
    bool isopen = capture.open(media_path);
    cv::Mat frame;
    while(capture.read(frame)){
        auto ret = yolov5_trt_detect(trt_engine, frame, conf_thresh,det);
        if(ret!= 0){
            //����ʶ��������
            showDetection(frame,det);
        }
        else {
            //û��ʶ�� ����ֱ������
            std::cout << "---------------failed______________________"<<std::endl;
            continue;
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
    cv::resize(temp, temp, cv::Size(output_cols, output_rows), 0, 0);
    outputVideo.write(temp);
    cv::waitKey(1);
}
