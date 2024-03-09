cmake_minimum_required(VERSION 3.12)  # 更新为较新版本

project(ImageProcessor)
set(CMAKE_CXX_STANDARD 11)  # 确保使用 C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# 查找OpenCV库
set(OpenCV_DIR "E:/Tools/OpenCV/opencv/build")
find_package(OpenCV QUIET
    NO_MODULE
    NO_DEFAULT_PATH
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_PACKAGE_REGISTRY
    NO_CMAKE_BUILDS_PATH
    NO_CMAKE_SYSTEM_PATH
    NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
)

# 打印OpenCV版本
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

# 打印包含目录
message(STATUS "OpenCV include path: ${OpenCV_INCLUDE_DIRS}")

# 打印链接库目录
message(STATUS "OpenCV library path: ${OpenCV_LIB_DIR}")

# 打印找到的所有OpenCV库
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

set(CMAKE_CUDA_COMPILER C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.1/bin/nvcc.exe)
enable_language(CUDA)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Threads REQUIRED)

# 移除不必要的添加定义
add_definitions(-DAPI_EXPORTS)

# 设置 CUDA NVCC 目标架构
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS};-g;-G;-gencode arch=compute_61,code=sm_61")

# 修正 include 和 link 目录
include_directories(
    E:/Tools/Eigen-/eigen
    ${CUDA_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/YOLO/include
    E:/Tools/Yolov5/TensorRT-8.6.1.6/include
    C:/Program\ Files/NVIDIA\ GPU\ Computing\ Toolkit/CUDA/v12.1/include
    ${PROJECT_SOURCE_DIR}/plugins/
)
link_directories(
    C:/Program\ Files/NVIDIA\ GPU\ Computing\ Toolkit/CUDA/v12.1/lib/x64
    E:/Tools/Yolov5/TensorRT-8.6.1.6/lib
    E:/Tools/OpenCV/opencv/build/x64/vc16/lib
)

# 编译 YOLO CUDA 库
file(GLOB YOLO_SRC_DIR "${PROJECT_SOURCE_DIR}/YOLO/src/*.cpp" "${PROJECT_SOURCE_DIR}/YOLO/src/*.cu")
message(STATUS "Compiling YOLO sources: ${YOLO_SRC_DIR}")
add_library(yolov5_trt SHARED ${YOLO_SRC_DIR})
target_link_libraries(yolov5_trt nvinfer cudart ${OpenCV_LIBS})
#set_target_properties(yolov5_trt PROPERTIES
   # ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  #  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
 #   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#)
message(STATUS "YOLO CUDA library compiled successfully")

# 编译主程序
file(GLOB_RECURSE PLUGIN_SRCS ${PROJECT_SOURCE_DIR}/plugins/*.cu)
add_library(myplugins SHARED ${PLUGIN_SRCS})
target_link_libraries(myplugins nvinfer cudart ${OpenCV_LIBS})
set_target_properties(myplugins PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src M_SRC_DIR)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(ImageProcessor ${M_SRC_DIR})
target_link_libraries(ImageProcessor Qt5::Core Qt5::Gui Qt5::Widgets ${CMAKE_THREAD_LIBS_INIT} yolov5_trt myplugins nvinfer cudart ${OpenCV_LIBS})
target_link_libraries(ImageProcessor Qt5::Widgets)

# 设置 Qt 配置
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
