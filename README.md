# face-rec
  
## 依赖

* cmake>=3.9
* dlib_19.6
* cuda_8.0
* cudnn_6

## Linux 安装库：

* 进入 `facedlib` 目录
* mkdir build && cd build
* cmake ..
* make .
* sudo make install

## Example

例子在 `main.cpp` 上, 输入两个图片的文件路径,支持 `.png` 和 `.jpg`，输出识别结果：

facerec 识别结果

* 1 第一幅图没有人脸
* 2 第二幅图没有人脸
* 4 有相同人脸
* 0 没有相同的人脸

faceidentify 识别结果

* 1 图中没有人脸
* 2 图中的人脸不是两个
* 4 两个人脸相同
* 0 两个人脸不同