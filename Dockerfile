FROM cybertailor/builder/1

RUN apt-get remove -y tensorrt
RUN apt-get remove -y libnvinfer-dev
RUN apt-get install -y --no-install-recommends \
    tensorrt 
ENV LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
#RUN useradd -m -d /home/saul -s /bin/bash -G sudo saul
#RUN echo 'saul:700101' | chpasswd
EXPOSE 22
# 定义容器启动时执行的命令
CMD ["bash"]