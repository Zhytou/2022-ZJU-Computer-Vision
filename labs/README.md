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
sudo apt update && sudo apt install -y cmake g++ wget unzip
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
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
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

## References

安装

- [opencv 官网安装](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)
- [opencv 安装](https://starrycat.me/wsl-1-opencv-compile-install-using-cmake.html)

运行

- [stack over flow](https://stackoverflow.com/questions/63455427/fatal-error-opencv2-opencv-modules-hpp-no-such-file-or-directory-include-ope)
