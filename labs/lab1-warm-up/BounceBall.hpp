#ifndef BOUNCEBALL
#define BOUNCEBALL
#include <iostream>
#include <cmath>
#include "opencv4/opencv2/opencv.hpp"

class BounceBall
{
private:
    // position
    int x, y;
    // speed
    int dx, dy;
    // radius
    int radius;
    // color
    cv::Scalar color;

    bool collapse(const BounceBall &);
public:
    BounceBall() = default;

    BounceBall(int bx, int by, int dbx, int dby, int br, const cv::Scalar& bc) : x(bx), y(by), dx(dbx), dy(dby), radius(br), color(bc) {}

    BounceBall(const BounceBall& other) {
        x = other.x;
        y = other.y;
        dx = other.dx;
        dy = other.dy;
        radius = other.radius;
        color = other.color;
    }

    ~BounceBall() {}

    friend void move(std::vector<BounceBall> &, const int&, const int&);

    void draw(cv::Mat &) const;
};

#endif