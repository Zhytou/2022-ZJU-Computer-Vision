#include <stdlib.h> 
#include <math.h>
#include <assert.h>
#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
#include "BounceBall.hpp"

#define FRAME_NUM 100
#define DELAY 300
using namespace std;
using namespace cv;

int RandInt(int max, int min = 0)
{
    assert(max > min);
    return rand() % (max - min) + min;
}

Scalar RandColor()
{
    return Scalar(RandInt(255), RandInt(255), RandInt(255));
}

int main(int argc, char **argv)
{
    // define size
    const int width = 600, height = 600;
    // create a img
    Mat img;
    const string windName = "lab1-warm-up";
    // create a window
    namedWindow(windName);
    // create a videowriter
    VideoWriter vw("./lab1_output.avi",
                   VideoWriter::fourcc('M', 'J', 'P', 'G'),
                   30.0,
                   Size(width, height),
                   true);

    /*
    // load my profile
    cout << "load my profile\n";
    img = imread("../lab1-warm-up/profile.png");
    for (int i = 0; i < FRAME_NUM; i++)
    {
        imshow(windName, img);
        //vw << img;
        if (waitKey(DELAY) == 32) {
            cout << "wait\n";
            waitKey(0);
            cout << "break\n";
        }
    }
    */
    
    // bounce balls
    cout << "bounce balls\n";
    // inialize
    int speed = 10, radius = 15;
    vector<BounceBall> balls(10);
    for (int i = 0; i < balls.size(); i++) {
        int ri = RandInt(2 * radius, radius), vi = RandInt(2 * speed, speed);
        int xi = RandInt(width / balls.size() * (i + 1) - ri, width / balls.size() * i + ri), yi = RandInt(height - ri, ri);
        balls[i] = BounceBall(xi, yi, vi, vi, ri, RandColor());
    }
    // move
    for (int i = 0; i < FRAME_NUM; i++) {
        img = Mat(width, height, CV_8UC3, Scalar(255, 255, 255));
        for (const auto &ball :balls) {
            ball.draw(img);
        }
        move(balls, width, height);
        imshow(windName, img);
        //vw << img;
        if (waitKey(DELAY) == 32) {
            cout << "wait\n";
            waitKey(0);
            cout << "break\n";
        }
    }
    
    // end the vedio
    cout << "end the vedio\n";

    // pause to quit
    waitKey(0);

    // type any character to quit the process
    cout << "quit"<< endl;

    // destroy window
    destroyWindow(windName);
    return 0;
}
