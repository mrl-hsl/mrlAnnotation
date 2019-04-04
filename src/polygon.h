#ifndef POLYGON_H
#define POLYGON_H

#include "selector.h"

class Polygon:public Selector{
public:
    ~Polygon();
    Polygon(){}
    void add_vertex(cv::Point2d);
    void remove_vertex(int num);
    void draw(cv::Mat *, cv::Vec3b);
    std::vector<cv::Point2d> get_points();
    std::vector<cv::Point2d> get_bounds();
    std::vector<cv::Point2d> get_vertices();
    void clean(cv::Mat *);
private:
    int X_Min=1000000,X_Max=0;
    int Y_Min=1000000,Y_Max=0;
    bool drawing=false;
    std::vector <cv::Point2d> bounds;
    std::vector<cv::Point2d> vertices;
    std::vector<cv::Point2d> pts;
};

#endif // POLYGON_H
