#include <algorithm>
#include <iostream>
#include <vector>

#include "opencv4/opencv2/opencv.hpp"

#define KEY_POINT_NUM 500
#define BEST_MATCH_POINT_NUM 10

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
  for (int imgIdx = 1; imgIdx <= 2; imgIdx++) {
    // 读取第 i 组图片
    char imgName[30];
    sprintf(imgName, "../lab2-stiching/img/%d1.jpg", imgIdx);
    Mat img1 = imread(imgName);
    imgName[0] = '\0';
    sprintf(imgName, "../lab2-stiching/img/%d2.jpg", imgIdx);
    Mat img2 = imread(imgName);

    // SIFT特征点检测器
    Ptr<SIFT> detector = SIFT::create(KEY_POINT_NUM);
    // 特征点
    vector<KeyPoint> keyPoints1, keyPoints2;

    // 进行特征检测
    detector->detect(img1, keyPoints1);
    detector->detect(img2, keyPoints2);

    // 展示特征点检测结果
    Mat detectImg1;
    drawKeypoints(img1, keyPoints1, detectImg1);
    imshow(detectWindName1, detectImg1);

    Mat detectImg2;
    drawKeypoints(img2, keyPoints2, detectImg2);
    imshow(detectWindName2, detectImg2);

    // 特征点描述提取器
    Ptr<SiftDescriptorExtractor> descriptor = SiftDescriptorExtractor::create();

    // 提取特征点描述符
    Mat describeImg1, describeImg2;
    descriptor->compute(img1, keyPoints1, describeImg1);
    descriptor->compute(img2, keyPoints2, describeImg2);

    // 特征匹配器
    BFMatcher matcher;
    vector<DMatch> matchPoints;
    // 实现描述符之间的匹配
    matcher.match(describeImg1, describeImg2, matchPoints);

    // 展示特征匹配结果
    Mat matchImg;
    drawMatches(img1, keyPoints1, img2, keyPoints2, matchPoints, matchImg);
    imshow(matchWindName, matchImg);

    // 找出图中匹配的最好的点
    sort(matchPoints.begin(), matchPoints.end());
    vector<Point2f> bestMatchPoints1, bestMatchPoints2;
    for (int i = 0; i < BEST_MATCH_POINT_NUM; i++) {
      bestMatchPoints1.push_back(keyPoints1[matchPoints[i].queryIdx].pt);
      bestMatchPoints2.push_back(keyPoints2[matchPoints[i].trainIdx].pt);
    }

    // 计算映射矩阵
    Mat transformMat =
        findHomography(bestMatchPoints1, bestMatchPoints2, RANSAC);

    // 计算匹配点，用于图像拼接定位

    // 进行图片变换
    Mat transformImg;
    warpPerspective(img1, transformImg, transformMat,
                    Size(img2.cols, img2.rows));

    // 拼接后图像
    int height = max(img1.rows, img2.rows), width = img1.cols + img2.cols;
    Mat stichImg(height, width, CV_8UC3);
    transformImg.copyTo(
        stichImg(Rect(0, 0, transformImg.cols, transformImg.rows)));
    img2.copyTo(stichImg(Rect(0, 0, img2.cols, img2.rows)));

    imshow(stichWindName, stichImg);
    waitKey(0);
  }

  return 0;
}