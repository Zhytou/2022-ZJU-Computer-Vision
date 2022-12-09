# CV-Labs

- [CV-Labs](#cv-labs)
  - [安装 \& 环境](#安装--环境)
  - [编译 \& 运行](#编译--运行)
  - [要求 \& 实现](#要求--实现)
    - [Lab1 Warm-up](#lab1-warm-up)
    - [Lab2 Image Stiching](#lab2-image-stiching)
  - [References](#references)

## 安装 & 环境

> 开发环境：VScode + WSL2 + Opencv + VcXsrv

安装Opencv

``` bash
# Install minimal prerequisites (Ubuntu 18.04 as reference) 
sudo apt update && sudo apt install -y cmake g++ wget unzip libgtk2.0-dev pkg-config
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
# Create build directory
mkdir -p build && cd build
# Configure
cmake  ../opencv-4.x
# Build
cmake --build .
# Install
make install
```

安装VcXsrv

> VcXsrv是一个开源软件，它可以为wsl的程序提供GUI窗口。

- [下载](https://sourceforge.net/projects/vcxsrv/)安装包

- 配置WSL环境

``` bash
# Edit config for console
vim ~/.bashrc or vim ~/.zshrc
# Add following to the end of file
export DISPLAY=:0
# Save and put the config into work
source ~/.bashrc or source ~/.zshrc
```

- 启动VcXsrv: 在安装目录，双击xlaunch启动服务。

## 编译 & 运行

``` bash
cd labs
mkdir build | cd build
cmake ../
make lab1 or lab2 or lab3
./lab1 or ./lab2 or ./lab3
```

## 要求 & 实现

### Lab1 Warm-up

![request](./lab1-warm-up/lab1.JPG)

整个程序主要分成五部分，包括：加载姓名和学号信息图片、加载个人照片并先后转化称灰度图和黑白图、生成简单图案（线段、矩形和圆形）、生成彩色弹珠和加载结束图片。

其中，每部分都是在一个 Mat 对象上操作，然后用一个 imshow 函数实现显示；接着，将该 Mat 对象导入一个 VideoWriter 对象实现视频存储；最后，通过 waitKey 函数实现了暂停功能。

对于彩色图转灰度图，则是将（存储图像的）Mat 对象同一个位置的三个色彩通道变成同一值。而灰度图进一步转为黑白图，则是三个色彩通道二值化（保证最后只有 0 和 255 两种值）。

除此之外，定义了一个 BounceBall 类记录弹珠位置、速度、大小和颜色信息，实现了 draw、collapse 和 move（友元函数）三个函数。

### Lab2 Image Stiching

整个程序分成四部分，包括：1、提取两张图片特征点并展示该结果；2、匹配两张图特征点并展示结果；3、计算变换矩阵，并利用矩阵转换得到新右图，最后展示直接拼接结果；4、加权计算拼接重叠部分，并最终实现融合拼接的效果。

检测特征点部分主要用到了：1、SIFT类，用create函数构造了一个SIFT的特征点检测器，并用类内detect函数保存结果；2、drawKeyPoints函数根据上述得到的特征点数组画出特征点检测结果。

特征点匹配部分主要用了：1、SiftDescriptorExtractor类，用create函数构造了一个SIFT的特征描述提取器，并用compute函数计算出描述符；2、BFMatcher类，调用类内函数match，根据上述特征描述符计算出匹配结果，最后用drawMatches画出匹配结果。

直接拼接部分主要用了：1、findHomography函数，从之前得到的匹配特征点中选出10匹配效果好的，调用findHomography计算出映射矩阵；2、warpPerspective函数，根据映射矩阵，使用warpPerspective函数计算出新右图；3、copyTo函数，在新右图左边位置复制原左图，得到直接拼接结果。

融合拼接部分主要用了：1、计算出重叠部分边界；2、重新计算重叠部分像素值。

## References

安装

- [opencv 官网安装](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)
- [opencv 安装](https://starrycat.me/wsl-1-opencv-compile-install-using-cmake.html)

运行

- [stack over flow](https://stackoverflow.com/questions/63455427/fatal-error-opencv2-opencv-modules-hpp-no-such-file-or-directory-include-ope)
