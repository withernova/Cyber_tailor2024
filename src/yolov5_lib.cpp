//yolov5_lib.cpp 
 
#include <logging.h>
#include <calibrator.h>
#include <iostream>
#include <chrono>
#include "cuda_runtime_api.h"
#include "postprocess.hpp"
#include "yolov5_lib.h"
#include "cuda_utils.h"
#include "utils.h"
#include "datatype.h"
#include "NvInfer.h"
using namespace nvinfer1;
#define USE_FP16  // comment out this if want to use FP32
#define DEVICE 0  // GPU id
#define NMS_THRESH 0.4
#define CONF_THRESH 0.3
#define BATCH_SIZE 1
using namespace Yolo;
// stuff we know about the network and the input/output blobs
//继承了yolo的一些属性（来源于Yololayer.h 大致是模型训练时选取的图形高度 宽度 以及可以识别的类的种类
static const int INPUT_H = Yolo::INPUT_H;
static const int INPUT_W = Yolo::INPUT_W;
static const int CLASS_NUM = Yolo::CLASS_NUM;
//这个是输出碰撞箱的内存大小（用于申请？
static const int OUTPUT_SIZE = Yolo::MAX_OUTPUT_BBOX_COUNT * sizeof(Yolo::Detection) / sizeof(float) + 1;  // we assume the yololayer outputs no more than MAX_OUTPUT_BBOX_COUNT boxes that conf >= 0.1
const char* INPUT_BLOB_NAME = "data";
const char* OUTPUT_BLOB_NAME = "prob";
// 这个logger来源于logging 暂时未解读 %%%%%%%%
static Logger gLogger;
 
 //进行模型推理的函数 传入初始化后的buffer 上下文 input output
static void doInference(IExecutionContext& context, cudaStream_t& stream, void **buffers, float* input, float* output, int batchSize) {
    //先初始化一个源buffer 然后将数据拷入该buffer
    //然后将源buffer拷入device的buffer
    //预处理
    // DMA input batch data to device, infer on the batch asynchronously, and DMA output back to host
    //CUDA_CHECK(cudaMemcpyAsync(buffers[0], input, batchSize * 3 * Yolo::INPUT_H * Yolo::INPUT_W * sizeof(float), cudaMemcpyHostToDevice, stream));
    //cudaMemcpyAsync(buffers[0], input, batchSize * 3 * Yolo::INPUT_H * Yolo::INPUT_W * sizeof(float), cudaMemcpyHostToDevice, stream);
    context.enqueue(batchSize, buffers, stream, nullptr);
    CUDA_CHECK(cudaMemcpyAsync(output, buffers[1], batchSize * OUTPUT_SIZE * sizeof(float), cudaMemcpyDeviceToHost, stream));
    //cudaMemcpyAsync(output, buffers[1], batchSize * OUTPUT_SIZE * sizeof(float), cudaMemcpyDeviceToHost, stream);
    //!!!!!!!!!!!!!!!!output在下一句后指针的值归零
    cudaStreamSynchronize(stream);
}
 
//static void prepare_buffers(ICudaEngine* engine, float** gpu_input_buffer, float** gpu_output_buffer, float** cpu_output_buffer) {
//    assert(engine->getNbBindings() == 2);
//    // In order to bind the buffers, we need to know the names of the input and output tensors.
//    // Note that indices are guaranteed to be less than IEngine::getNbBindings()
//    const int inputIndex = engine->getBindingIndex(kInputTensorName);
//    const int outputIndex = engine->getBindingIndex(kOutputTensorName);
//    assert(inputIndex == 0);
//    assert(outputIndex == 1);
//    // Create GPU buffers on device
//    CUDA_CHECK(cudaMalloc((void**)gpu_input_buffer, kBatchSize * 3 * kInputH * kInputW * sizeof(float)));
//    CUDA_CHECK(cudaMalloc((void**)gpu_output_buffer, kBatchSize * kOutputSize * sizeof(float)));
//
//    *cpu_output_buffer = new float[kBatchSize * kOutputSize];
//}
 
typedef struct 
{
//上下文结构体 包含数据啊 引擎啊 缓冲区之类的部分
    float *data;
    float *prob;
    IRuntime *runtime;
    ICudaEngine *engine;
    IExecutionContext *exe_context;
    void* buffers[2];
    cudaStream_t cuda_stream;
    int inputIndex;
    int outputIndex;
    char result_json_str[16384];
 
}Yolov5TRTContext;

//深度跟踪 不需要我们了解
typedef struct{
	int class_id;
	int x1;
	int y1;
	int x2; 
	int y2;
	float conf;
	
}DeepsortContext;

//用于根据模型路径创建模型 这个创建过程应该不用很详细的了解 但是到时候可能要我们复现
void * yolov5_trt_create(const char * engine_name)
{
    size_t size = 0;
    char *trtModelStream = NULL;
    //初始化了一个上下文对象 一个size 一个模型流字符串
    Yolov5TRTContext * trt_ctx = NULL;
 
    trt_ctx = new Yolov5TRTContext();
 
    std::ifstream file(engine_name, std::ios::binary);
    //开始读入模型数据
    printf("yolov5_trt_create  ... \n");
    if (file.good()) {
        file.seekg(0, file.end);
        size = file.tellg();
        file.seekg(0, file.beg);
        trtModelStream = new char[size];
        assert(trtModelStream);
        file.read(trtModelStream, size);
        file.close();
    }else
        return NULL;
 
    trt_ctx->data = new float[BATCH_SIZE * 3 * Yolo::INPUT_H * Yolo::INPUT_W];
    trt_ctx->prob = new float[BATCH_SIZE * OUTPUT_SIZE];
    /*GPT解释
    这段代码是用在基于TensorRT的深度学习应用程序中。让我逐步解释每一部分：

    trt_ctx->runtime = createInferRuntime(gLogger);

    这一行创建了一个新的 TensorRT 推理(runtime)环境，并将其指针赋值给 trt_ctx 结构体中的 runtime 成员。createInferRuntime 是一个函数，用于初始化一个 TensorRT 推理环境。这个环境是执行模型推理所必需的。gLogger 是一个日志记录器实例，用于记录 TensorRT 运行时的日志信息，帮助开发者了解运行时发生了什么。

    assert(trt_ctx->runtime != nullptr);

    这一行使用 assert 语句来确保 trt_ctx->runtime 已经被成功初始化。在这里，trt_ctx->runtime != nullptr 是一个条件，它检查 trt_ctx->runtime 是否不是空指针（即确保 createInferRuntime 调用成功，并且返回了一个有效的指针）。如果 trt_ctx->runtime 为 nullptr，这意味着创建推理(runtime)环境失败，那么程序将显示一个断言错误并终止。这是一种防御性编程技巧，用于确保程序的关键组件被正确初始化，从而防止后续操作在无效的对象上执行。

简而言之，这两行代码的目的是创建一个TensorRT推理环境，并确保这个环境被成功创建。如果环境没有成功创建，程序将报错并停止执行，以避免进一步的不确定行为。
    */
    trt_ctx->runtime = createInferRuntime(gLogger);
    assert(trt_ctx->runtime != nullptr);
 
    printf("yolov5_trt_create  cuda engine... \n");
    trt_ctx->engine = trt_ctx->runtime->deserializeCudaEngine(trtModelStream, size);
    assert(trt_ctx->engine != nullptr);
    trt_ctx->exe_context = trt_ctx->engine->createExecutionContext();
 
 
    delete[] trtModelStream;
    assert(trt_ctx->engine->getNbBindings() == 2);
 
    // In order to bind the buffers, we need to know the names of the input and output tensors.
    // Note that indices are guaranteed to be less than IEngine::getNbBindings()
    trt_ctx->inputIndex = trt_ctx->engine->getBindingIndex(INPUT_BLOB_NAME);
    trt_ctx->outputIndex = trt_ctx->engine->getBindingIndex(OUTPUT_BLOB_NAME);
 
    assert(trt_ctx->inputIndex == 0);
    assert(trt_ctx->outputIndex == 1);
    // Create GPU buffers on device
 
    printf("yolov5_trt_create  buffer ... \n");
    CUDA_CHECK(cudaMalloc(&trt_ctx->buffers[trt_ctx->inputIndex], BATCH_SIZE * 3 * Yolo::INPUT_H * Yolo::INPUT_W * sizeof(float)));
    //cudaMalloc(&trt_ctx->buffers[trt_ctx->inputIndex], BATCH_SIZE * 3 * Yolo::INPUT_H * Yolo::INPUT_W * sizeof(float));
    CUDA_CHECK(cudaMalloc(&trt_ctx->buffers[trt_ctx->outputIndex], BATCH_SIZE * OUTPUT_SIZE * sizeof(float)));
    //cudaMalloc(&trt_ctx->buffers[trt_ctx->outputIndex], BATCH_SIZE * OUTPUT_SIZE * sizeof(float));
    // Create stream
 
    printf("yolov5_trt_create  stream ... \n");
    CUDA_CHECK(cudaStreamCreate(&trt_ctx->cuda_stream));
    //cudaStreamCreate(&trt_ctx->cuda_stream);
    printf("yolov5_trt_create  done ... \n");
    return (void *)trt_ctx;
 
 
}
 
 //这个是检测部分 应该是重点
int yolov5_trt_detect(void* h, cv::Mat& img, float threshold, std::vector<DetectBox>& det)
{
    //还是新建一个指针 用于接受h 将其明确成Yolov5TRTContext类型 
    Yolov5TRTContext* trt_ctx;
    int i;
    int delay_preprocess;
    int delay_infer;

    trt_ctx = (Yolov5TRTContext*)h;


    trt_ctx->result_json_str[0] = 0;
    // whether det is empty , if not, empty det
    //确保返回的det数组为空 图像资源不为空
    if (!det.empty()) det.clear();
    if (img.empty()) return 0;
    //这个是算延迟的可以不看
    auto start0 = std::chrono::system_clock::now();

    //printf("yolov5_trt_detect start preprocess img \n");
    //cv::Mat pr_img = preprocess_img(img, Yolo::INPUT_W, Yolo::INPUT_H);
    //std::cout<<"after preprocess_img pr_img size:"<<pr_img.cols<<" "<<pr_img.rows<<std::endl;
    //std::cout<<"after preprocess_img frame size:"<<img.cols<<" "<<img.rows<<std::endl;


    //printf("yolov5_trt_detect start convert img to float\n");
    // letterbox BGR to RGB
    /*
    i = 0;
    ////将图像的像素导入trt的data中
    for (int row = 0; row < Yolo::INPUT_H; ++row) {
        uchar* uc_pixel = pr_img.data + row * pr_img.step;
        for (int col = 0; col < Yolo::INPUT_W; ++col) {
            trt_ctx->data[i] = (float)uc_pixel[2] / 255.0;
            trt_ctx->data[i + Yolo::INPUT_H * Yolo::INPUT_W] = (float)uc_pixel[1] / 255.0;
            trt_ctx->data[i + 2 * Yolo::INPUT_H * Yolo::INPUT_W] = (float)uc_pixel[0] / 255.0;
            uc_pixel += 3;
            ++i;
        }
    }
    //依旧是时间
    */
    auto end0 = std::chrono::system_clock::now();

    delay_preprocess =  std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0).count();

    cuda_preprocess_init(kMaxInputImageSize);
    //preprocess
    cuda_preprocess(img.ptr(), img.cols, img.rows, (float*)trt_ctx->buffers[0], Yolo::INPUT_W, Yolo::INPUT_H, trt_ctx->cuda_stream);



    // Run inference
    //printf("yolov5_trt_detect start do inference\n");
    auto start = std::chrono::system_clock::now();
    //进行模型推理 将所有的数据送进去了
    doInference(*trt_ctx->exe_context, trt_ctx->cuda_stream, trt_ctx->buffers, trt_ctx->data, trt_ctx->prob, BATCH_SIZE);

    auto end = std::chrono::system_clock::now();
    delay_infer = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "delay_proress:" << delay_preprocess << "ms, " << "delay_infer:" << delay_infer << "ms" << std::endl;

    //printf("yolov5_trt_detect start do process infer result \n");

    int fcount = 1;
    int str_len;
    std::vector<std::vector<Yolo::Detection>> batch_res(1);
    //返回的数据批 用指针保留首地址
    auto& res = batch_res[0];

    //非极大值抑制（Non-Maximum Suppression, NMS）非极大值抑制用于消除多余的重叠边界框，保留最佳的那个。
/*
        对检测结果按照置信度进行排序。
    遍历排序后的检测结果，使用 iou 函数（Intersection over Union，交并比）来计算两个边界框的重叠程度。
    如果重叠程度高于 nms_thresh，则从列表中删除重叠的边界框。
    保留当前的边界框并继续对后续边界框进行此过程。
*/
    nms(res, &trt_ctx->prob[0], threshold, NMS_THRESH);


    i = 0;
    //对返回的数据流中的碰撞箱数据进行绑定 加入到det数组中 返回获取数据
    for (i = 0; i < res.size(); i++) {
        int x1, y1, x2, y2;
        int class_id;
        float conf;
        cv::Rect r = get_rect(img, res[i].bbox);
        DetectBox dd(r.x, r.y, r.x + r.width, r.y + r.height, (float)res[i].conf, (int)res[i].class_id);
        det.push_back(dd);
    }
    return 1;
}
 
 //一个替代性的析构函数
void yolov5_trt_destroy(void *h)
{
    Yolov5TRTContext *trt_ctx;
 
    trt_ctx = (Yolov5TRTContext *)h;
 
    // Release stream and buffers
    cudaStreamDestroy(trt_ctx->cuda_stream);
    CUDA_CHECK(cudaFree(trt_ctx->buffers[trt_ctx->inputIndex]));
    //cudaFree(trt_ctx->buffers[trt_ctx->inputIndex]);
    CUDA_CHECK(cudaFree(trt_ctx->buffers[trt_ctx->outputIndex]));
    //cudaFree(trt_ctx->buffers[trt_ctx->outputIndex])
    // Destroy the engine
    trt_ctx->exe_context->destroy();
    trt_ctx->engine->destroy();
    trt_ctx->runtime->destroy();
 
    delete trt_ctx->data;
    delete trt_ctx->prob;
 
    delete trt_ctx;
 
}

