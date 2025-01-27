#include "BounceBall.hpp"

using namespace std;

void move(vector<BounceBall> &balls, const int &width, const int &height) {
  // change balls position
  for (int i = 0; i < balls.size(); i++) {
    // check the window boundary
    if (balls[i].x + balls[i].dx < balls[i].radius ||
        balls[i].x + balls[i].dx > width - balls[i].radius ||
        balls[i].y + balls[i].dy < balls[i].radius ||
        balls[i].y + balls[i].dy > height - balls[i].radius) {
      if ((balls[i].x + balls[i].dx < balls[i].radius ||
           balls[i].x + balls[i].dx > width - balls[i].radius) &&
          (balls[i].y + balls[i].dy < balls[i].radius ||
           balls[i].y + balls[i].dy > height - balls[i].radius)) {
        balls[i].dx = -balls[i].dx;
        balls[i].dy = -balls[i].dy;
      } else if (balls[i].x + balls[i].dx < balls[i].radius ||
                 balls[i].x + balls[i].dx > width - balls[i].radius) {
        balls[i].dx = -balls[i].dx;
      } else {
        balls[i].dy = -balls[i].dy;
      }
    }

    // check other balls
    for (int j = 0; j < balls.size(); j++) {
      if (i == j) {
        continue;
      }

      if (balls[i].collapse(balls[j]) == true) {
        // for rear-end collision, exchange speed
        // for head-on collision, change speed direction
        if (balls[i].dx * balls[j].dx > 0) {
          int tmp = balls[i].dx;
          balls[i].dx = balls[j].dx;
          balls[j].dx = tmp;
        } else {
          balls[i].dx = -balls[i].dx;
          balls[j].dx = -balls[j].dx;
        }

        if (balls[i].dy * balls[j].dy > 0) {
          int tmp = balls[i].dy;
          balls[i].dy = balls[j].dy;
          balls[j].dy = tmp;
        } else {
          balls[j].dy = -balls[j].dy;
          balls[i].dy = -balls[i].dy;
        }
      }
    }

    balls[i].x += balls[i].dx;
    balls[i].y += balls[i].dy;
  }
}

void BounceBall::draw(cv::Mat &img) const {
  cv::circle(img, cv::Point(x, y), radius, color, -1);
}

bool BounceBall::collapse(const BounceBall &other) {
  double distance = sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
  if (distance > radius + other.radius)
    return false;
  else
    return true;
}