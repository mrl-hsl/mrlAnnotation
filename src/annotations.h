#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H

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

struct goalPost{
    std::vector<cv::Point> points;
};

struct bbox{
  bbox(){}
  bbox(cv::Rect _box,int _type):box(_box),type(_type){}
  cv::Rect box;
  int type;
};

#endif // ANNOTATIONS_H
