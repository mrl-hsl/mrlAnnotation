#ifndef LINE_H
#define LINE_H
#include "selector.h"

class Line:public Selector{
public:
    Line(){}
    void draw(cv::Mat *,cv::Scalar,int Thickness=1);
    void clean(cv::Mat *);
    void is_drawing(bool);
    bool is_drawing();
    void set_thickness(int);
    int get_thickness();
    void set_point1(cv::Point2d);
    void set_point2(cv::Point2d);
    cv::Point2d get_point1();
    cv::Point2d get_point2();
    cv::Scalar get_color();
private:
    cv::Point2d Pt1,Pt2;
    cv::Scalar color;
    int thickness=1;
    bool drawing=false;
};

#endif // LINE_H
