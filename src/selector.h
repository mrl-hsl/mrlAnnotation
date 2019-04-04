#ifndef SELECTORS_H
#define SELECTORS_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "sample.h"
struct Polygon{
    Polygon() {}
    std::vector<cv::Point> points;
    typedef std::vector<cv::Point>::iterator iterator;
    iterator begin(){return points.begin();}
    iterator end(){return points.end();}
};
struct Line{
    Line() {}
    cv::Point p1,p2;
};
class Selector{
public:
    Selector (){}
    ~Selector(){}
    void setStatus(bool);
    bool is_drawing();

    void selectBox(cv::Point,int);
    void selectPolygon(cv::Point,int);
    void selectLine(cv::Point,int);
    void selectSegment(cv::Scalar,int);

private:
    bool drawing = false;
    std::vector<cv::Point2d> pts;
    std::vector<bbox> objects;
    std::vector<Polygon> polygons;
    std::vector<Line> lines;
    cv::Mat mask;


};

#endif // SELECTORS_H
