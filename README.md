# face-rec

依赖：
cmake>=3.9
dlib_19.6
cuda_8.0
cudnn_6
------------------------------------

Linux安装库：
进入facedlib目录
mkdir build && cd build
cmake ..
make .
sudo make install

-------------------------------------

例子在main.cpp上
faceRecognition类
faceRecognition构造函数，是两个图片的文件路径支持.png .jpg
facerecd方法参数为识别阈值，输出中间结果
facerec方法参数为识别阈值，不输出中间结果
返回值1 第一幅图没有人脸
返回值2 第二幅图没有人脸
返回值4 有相同人脸
返回值0 没有相同的人脸

--------------------------------------
