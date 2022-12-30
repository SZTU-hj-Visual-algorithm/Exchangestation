//
// Created by fly on 22-12-29.
//

#ifndef DUIHUANSTATION_EXCHANGESTATION_H
#define DUIHUANSTATION_EXCHANGESTATION_H
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
#define Red 1
#define Blue 0
class station{
public:
    void setinfo(Mat image, int realcolor);
    void changeMat(Mat image);
    Mat pre_img();
    Point2f process(float *tr);

private:
    int color;
    Mat src;
};

#endif //DUIHUANSTATION_EXCHANGESTATION_H
