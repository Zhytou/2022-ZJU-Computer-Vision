#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "BounceBall.hpp"


#define FRAME_NUM 20
#define DELAY 300
using namespace std;
using namespace cv;

// return a random integer in [min, max)
int RandInt(int max, int min = 0) {
  assert(max >= min);
  return rand() % (max - min) + min;
}

Scalar RandColor() { return Scalar(RandInt(255), RandInt(255), RandInt(255)); }

void RandPattern(Mat &img, int xlow, int xhigh, int ylow, int yhigh) {
  int x, y, nx, ny;
  int x1, x2, y1, y2;
  int r;
  switch (RandInt(3)) {
    case 1:
      // circle
      x = RandInt(xhigh, xlow), y = RandInt(yhigh, ylow);
      r = xhigh - xlow > yhigh - ylow ? RandInt(yhigh - ylow)
                                      : RandInt(xhigh - xlow);
      circle(img, Point(x, y), r, RandColor(), -1);
      break;
    case 2:
      // rectangle
      x1 = RandInt(xhigh, xlow), y1 = RandInt(yhigh, ylow);
      x2 = RandInt(xhigh, x1), y2 = RandInt(yhigh, y1);
      rectangle(img, Point(x1, y1), Point(x2, y2), RandColor(), -1);
      break;
    default:
      // line
      x = RandInt(xhigh, xlow), y = RandInt(yhigh, ylow);
      nx = RandInt(xhigh, xlow), ny = RandInt(yhigh, ylow);
      line(img, Point(x, y), Point(nx, ny), RandColor(), 2);
      break;
  }
}

int main(int argc, char **argv) {
  // define size (equal to the size of the info.png, profile.png and end.png)
  const int width = 960, height = 720;
  // create a img
  Mat img;
  const char windName[] = "lab1-warm-up";
  // create a window
  namedWindow(windName);
  // create a videowriter
  VideoWriter vw("./lab1_output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'),
                 30.0, Size(width, height), true);

  // load my info
  cout << "load my infomation\n";
  img = imread("../lab1-warm-up/info.png");
  for (int i = 0; i < FRAME_NUM; i++) {
    imshow(windName, img);
    vw << img;
    if (waitKey(DELAY) == 32) {
      cout << "wait\n";
      waitKey(0);
      cout << "break\n";
    }
  }

  // load my profile and convert to grayscale image
  cout << "load my profile and convert to grayscale image\n";
  img = imread("../lab1-warm-up/profile.jpg");
  int rows = 0;
  for (int i = 0; i < FRAME_NUM; i++) {
    while (rows < height / FRAME_NUM * (i + 1) && rows < height) {
      for (int cols = 0; cols < width; cols++) {
        int b = img.at<Vec3b>(rows, cols)[0];
        int g = img.at<Vec3b>(rows, cols)[1];
        int r = img.at<Vec3b>(rows, cols)[2];

        img.at<Vec3b>(rows, cols)[0] = 0.33 * (r + g + b);
        img.at<Vec3b>(rows, cols)[1] = 0.33 * (r + g + b);
        img.at<Vec3b>(rows, cols)[2] = 0.33 * (r + g + b);
      }
      rows += 1;
    }
    imshow(windName, img);
    vw << img;
    if (waitKey(DELAY) == 32) {
      cout << "wait\n";
      waitKey(0);
      cout << "break\n";
    }
  }

  // then convert to black and white image
  cout << "then convert to black and white image\n";
  int threhold = 128;
  rows = 0;
  for (int i = 0; i < FRAME_NUM; i++) {
    while (rows < height / FRAME_NUM * (i + 1) && rows < height) {
      for (int cols = 0; cols < width; cols++) {
        for (int channel = 0; channel < 3; channel++) {
          if (img.at<Vec3b>(rows, cols)[channel] >= threhold)
            img.at<Vec3b>(rows, cols)[channel] = 255;
          else
            img.at<Vec3b>(rows, cols)[channel] = 0;
        }
      }
      rows += 1;
    }
    imshow(windName, img);
    vw << img;
    if (waitKey(DELAY) == 32) {
      cout << "wait\n";
      waitKey(0);
      cout << "break\n";
    }
  }

  // draw some simple random patterns
  cout << "draw some simple random patterns\n";
  // initialize "a white paper"
  img = Mat(Size(width, height), CV_8UC3, Scalar(255, 255, 255));
  // initialize a point
  for (int i = 0; i < FRAME_NUM; i++) {
    RandPattern(img, 0, width, 0, height);
    imshow(windName, img);
    vw << img;
    if (waitKey(DELAY) == 32) {
      cout << "wait\n";
      waitKey(0);
      cout << "break\n";
    }
  }

  // bounce balls
  cout << "bounce balls\n";
  // inialize
  int speed = 10, radius = 15;
  vector<BounceBall> balls(10);
  for (int i = 0; i < balls.size(); i++) {
    int ri = RandInt(2 * radius, radius), vi = RandInt(2 * speed, speed);
    int xi = RandInt(width / balls.size() * (i + 1) - ri,
                     width / balls.size() * i + ri),
        yi = RandInt(height - ri, ri);
    balls[i] = BounceBall(xi, yi, vi, vi, ri, RandColor());
  }
  // move
  for (int i = 0; i < FRAME_NUM * 5; i++) {
    img = Mat(Size(width, height), CV_8UC3, Scalar(255, 255, 255));
    for (const auto &ball : balls) {
      ball.draw(img);
    }
    move(balls, width, height);
    imshow(windName, img);
    vw << img;
    if (waitKey(DELAY) == 32) {
      cout << "wait\n";
      waitKey(0);
      cout << "break\n";
    }
  }

  // end the vedio
  cout << "end the vedio\n";
  img = imread("../lab1-warm-up/end.png");
  for (int i = 0; i < FRAME_NUM / 5; i++) {
    imshow(windName, img);
    vw << img;
    if (waitKey(DELAY) == 32) {
      cout << "wait\n";
      waitKey(0);
      cout << "break\n";
    }
  }

  // type any character to quit the process
  cout << "type any character to quit" << endl;

  // pause to quit
  waitKey(0);

  // destroy window
  destroyWindow(windName);
  return 0;
}
