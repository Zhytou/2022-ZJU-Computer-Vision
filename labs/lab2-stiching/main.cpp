#include <algorithm>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define KEY_POINT_NUM 500
#define GOOD_MATCH_POINT_NUM 10

using namespace std;
using namespace cv;

int main() {
  // 创建窗口用于展示
  const char detectWindName1[] = "lab2-detect-results1",
             detectWindName2[] = "lab2-detect-results2";
  const char matchWindName[] = "lab2-match-results";
  const char stichWindName[] = "lab2-stich-results";
  const char blendWindName[] = "lab2-blend-results";
  namedWindow(detectWindName1, 0);
  namedWindow(detectWindName2, 0);
  namedWindow(matchWindName, 0);
  namedWindow(stichWindName, 0);
  namedWindow(blendWindName, 0);

  // 拼接 5 组图片
  for (int imgIdx = 1; imgIdx <= 5; imgIdx++) {
    // 读取第 i 组图片
    char imgName[30];
    sprintf(imgName, "../lab2-stiching/img/%d1.jpg", imgIdx);
    // 读取右图
    Mat img1 = imread(imgName);
    imgName[0] = '\0';
    sprintf(imgName, "../lab2-stiching/img/%d2.jpg", imgIdx);
    // 读取左图
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
    vector<Point2f> goodMatchPoints1, goodMatchPoints2;
    for (int i = 0; i < GOOD_MATCH_POINT_NUM; i++) {
      goodMatchPoints1.push_back(keyPoints1[matchPoints[i].queryIdx].pt);
      goodMatchPoints2.push_back(keyPoints2[matchPoints[i].trainIdx].pt);
    }

    // 计算映射矩阵
    Mat transformMat = findHomography(goodMatchPoints1, goodMatchPoints2);

    // 进行图片变换
    Mat newImg1;
    warpPerspective(img1, newImg1, transformMat,
                    Size(img1.cols + img2.cols, max(img1.rows, img2.rows)));
    // 拼接后图像
    Mat stichImg(newImg1);
    img2.copyTo(stichImg(Rect(0, 0, img2.cols, img2.rows)));
    imshow(stichWindName, stichImg);

    // 图像融合
    Mat blendImg(Size(img1.cols + img2.cols, max(img1.rows, img2.rows)),
                 CV_8UC3, Scalar(255, 255, 255));

    // 计算重叠部分上下边界
    vector<Point2f> sourceCornerPoints(4), targetCornerPoints(4);
    sourceCornerPoints[0] = Point2f(0, 0);
    sourceCornerPoints[1] = Point2f(img1.cols, 0);
    sourceCornerPoints[2] = Point2f(img1.cols, img1.rows);
    sourceCornerPoints[3] = Point2f(0, img1.rows);
    perspectiveTransform(sourceCornerPoints, targetCornerPoints, transformMat);

    int low = int(min(targetCornerPoints[0].x, targetCornerPoints[3].x));
    int high = img2.cols;
    int overlapWidth = high - low + 1;

    cout << low << ' ' << high << endl;
    cout << blendImg.cols << ' ' << blendImg.rows << endl;

    newImg1.copyTo(blendImg(Rect(0, 0, newImg1.cols, newImg1.rows)));
    img2.copyTo(blendImg(Rect(0, 0, img2.cols, img2.rows)));

    warpPerspective(img1, newImg1, transformMat,
                    Size(img1.cols + img2.cols, max(img1.rows, img2.rows)));

    // 加权融合
    for (int i = 0; i < blendImg.rows; i++) {
      for (int j = low; j <= high; j++) {
        if (newImg1.at<Vec3b>(i, j)[0] == 0 &&
            newImg1.at<Vec3b>(i, j)[1] == 0 &&
            newImg1.at<Vec3b>(i, j)[2] == 0) {
          blendImg.at<Vec3b>(i, j) = img2.at<Vec3b>(i, j);
        } else {
          double fraction = 1.0 * (j - low) / overlapWidth;
          blendImg.at<Vec3b>(i, j) = fraction * newImg1.at<Vec3b>(i, j) +
                                     (1 - fraction) * img2.at<Vec3b>(i, j);
        }
      }
    }
    /*
    for (int i = 0; i < blendImg.rows; i++) {
      for (int j = 0; j < low; j++) {
        blendImg.at<Vec3b>(i, j) = img2.at<Vec3b>(i, j);
      }
      for (int j = low - 1; j <= high + 1; j++) {
        if (newImg1.at<Vec3b>(i, j)[0] == 0 &&
            newImg1.at<Vec3b>(i, j)[1] == 0 &&
            newImg1.at<Vec3b>(i, j)[2] == 0) {
          blendImg.at<Vec3b>(i, j) = img2.at<Vec3b>(i, j);
        } else {
          double fraction = 1.0 * (j - low) / overlapWidth;
          blendImg.at<Vec3b>(i, j) = fraction * newImg1.at<Vec3b>(i, j) +
                                     (1 - fraction) * img2.at<Vec3b>(i, j);
        }
      }
      for (int j = high + 1; j < blendImg.cols; j++) {
        blendImg.at<Vec3b>(i, j) = newImg1.at<Vec3b>(i, j);
      }
    }
    */

    imshow(blendWindName, blendImg);
    waitKey(0);
  }

  return 0;
}