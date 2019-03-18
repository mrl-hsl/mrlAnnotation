#ifndef SELECTORS_H
#define SELECTORS_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Selector{
public:
    Selector (){}
    ~Selector(){}
    void is_drawing(bool);
    bool is_drawing();
private:
    bool drawing = false;
    std::vector<cv::Point2d> pts;
};

#endif // SELECTORS_H
