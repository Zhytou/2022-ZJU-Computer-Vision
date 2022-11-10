# CV-Labs

## 安装 & 环境

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

## 运行 & 检查

``` bash
cd labs
mkdir build | cd build
cmake ../
make lab1 | lab2 | lab3
./lab1 | ./lab2 | lab3
```

## 要求 & 实现

### Lab1 Warm-up

![request](./lab1-warm-up/lab1.JPG)

## References

安装

+ [opencv 官网安装](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)
+ [opencv 安装](https://starrycat.me/wsl-1-opencv-compile-install-using-cmake.html)

运行

+ [stack over flow](https://stackoverflow.com/questions/63455427/fatal-error-opencv2-opencv-modules-hpp-no-such-file-or-directory-include-ope)
