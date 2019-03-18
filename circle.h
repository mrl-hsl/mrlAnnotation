#ifndef CIRCLE_H
#define CIRCLE_H
#include "selector.h"
class  Circle:public Selector{
public:
    Circle();
    Circle(int,cv::Point2d);
    ~Circle(){
    }
    void set_radius(int );
    void set_centre(cv::Point2d );
    void draw(cv::Mat *, cv::Vec3b , int thickness=-1);
    int get_radius();
    cv::Point2d get_centre();
    void clean(cv::Mat*);
    void Fill();
private:
    int radius = 0;
    cv::Point2d centre;
//    bool drawing=false;
//    std::vector<cv::Point2d> pts;
};
#endif // CIRCLE_H
