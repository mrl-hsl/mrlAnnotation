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
    void push(cv::Point &point){points.push_back(point);}
    int type;
};
struct Line{
    Line() {}
    cv::Point p1,p2;
    int type;
};
class Selector{
public:
    std::vector<bbox> objects;
    std::vector<Polygon> polygons;
    std::vector<Line> lines;
    Line tLine;
    Polygon tPolygons;
    bbox tBox;

    Selector (){}
    ~Selector(){}
    void setStatus(bool);
    bool is_drawing();

    void selectBox(cv::Point,int);
    void selectPolygon(cv::Point,int);
    void selectLine(cv::Point,int);
    void selectSegment(cv::Scalar,int);
    void removeBox(cv::Point);
    inline bool inBox(cv::Point,cv::Rect);
private:
    bool drawing = false;
    std::vector<cv::Point2d> pts;
    cv::Mat mask;



};

#endif // SELECTORS_H
