#ifndef BOUNCEBALL
#define BOUNCEBALL
#include <cmath>
#include <iostream>

#include "opencv4/opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class BounceBall {
 private:
  // position
  int x, y;
  // speed
  int dx, dy;
  // radius
  int radius;
  // color
  Scalar color;

  bool collapse(const BounceBall &);

 public:
  BounceBall() = default;

  BounceBall(int bx, int by, int dbx, int dby, int br, const Scalar &bc)
      : x(bx), y(by), dx(dbx), dy(dby), radius(br), color(bc) {}

  BounceBall(const BounceBall &other) {
    x = other.x;
    y = other.y;
    dx = other.dx;
    dy = other.dy;
    radius = other.radius;
    color = other.color;
  }

  ~BounceBall() {}

  friend void move(vector<BounceBall> &, const int &, const int &);

  void draw(Mat &) const;
};

#endif