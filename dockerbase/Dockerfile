# 选择合适的CUDA和Ubuntu版本
FROM nvidia/cuda:12.1.0-cudnn8-devel-ubuntu20.04


# 设置环境变量
ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES compute,utility
ENV TZ Asia/Shanghai



RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get update \
    && apt-get install -y tzdata \
    && ln -fs /usr/share/zoneinfo/Asia/Shanghai /etc/localtime \
    && dpkg-reconfigure --frontend noninteractive tzdata
# 安装你的应用所需的其他必要软件和库
RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-default \
    qtdeclarative5-dev \
    qttools5-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*
    
