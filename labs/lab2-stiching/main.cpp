#include <iostream>
#include <vector>

#include "opencv4/opencv2/opencv.hpp"

#define KEY_POINT_NUM 500

using namespace std;
using namespace cv;

int main() {
  // 创建窗口用于展示
  const char detectWindName1[] = "lab2-detect-results1",
             detectWindName2[] = "lab2-detect-results2";
  const char matchWindName[] = "lab2-match-results";
  const char stichWindName[] = "lab2-stich-results";
  namedWindow(detectWindName1, 0);
  namedWindow(detectWindName2, 0);
  namedWindow(matchWindName, 0);
  namedWindow(stichWindName, 0);

  // 拼接 5 组图片
  for (int i = 1; i <= 5; i++) {
    // 读取第 i 组图片
    char imgName[30];
    sprintf(imgName, "../lab2-stiching/img/%d1.jpg", i);
    Mat img1 = imread(imgName);
    imgName[0] = '\0';
    sprintf(imgName, "../lab2-stiching/img/%d2.jpg", i);
    cout << imgName << endl;
    Mat img2 = imread(imgName);

    // SIFT特征点检测器
    Ptr<SIFT> detector = SIFT::create(KEY_POINT_NUM);
    // 特征点
    vector<KeyPoint> keypoints1, keypoints2;

    // 进行特征检测
    detector->detect(img1, keypoints1);
    detector->detect(img2, keypoints2);

    // 展示特征点检测结果
    Mat detectImg1;
    drawKeypoints(img1, keypoints1, detectImg1);
    imshow(detectWindName1, detectImg1);

    Mat detectImg2;
    drawKeypoints(img2, keypoints2, detectImg2);
    imshow(detectWindName2, detectImg2);

    // 特征点描述提取器
    Ptr<SiftDescriptorExtractor> descriptor = SiftDescriptorExtractor::create();

    // 提取特征点描述符
    Mat describeImg1, describeImg2;
    descriptor->compute(img1, keypoints1, describeImg1);
    descriptor->compute(img2, keypoints2, describeImg2);

    // 进行BFMatch暴力匹配
    BFMatcher matcher(NORM_L2);
    // 定义匹配结果变量
    vector<DMatch> matches;
    // 实现描述符之间的匹配
    matcher.match(describeImg1, describeImg1, matches);

    Mat matchImg;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, matchImg);
    imshow(matchWindName, matchImg);

    waitKey(0);
  }

  return 0;
}