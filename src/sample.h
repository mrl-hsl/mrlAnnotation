#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct goalPost{
    std::vector<cv::Point> points;
};
struct bbox{
  bbox(){}
  bbox(cv::Rect _box,int _type):box(_box),type(_type){}
  cv::Rect box;
  int type;
};

class sample{

public:

    sample(std::string address,std::string name):fileAddress(address),fileName(name){}
    sample();
    void imRead();

    void setSMask(cv::Mat _sMask);
    void removeSegment(cv::Vec3b color);

    cv::Mat getImg();
    cv::Mat getMask();
    cv::Mat getSMask();
    cv::Mat getSelectsMask();
    std::string getName();
    std::string getPath();

    typedef std::vector<bbox>::iterator iterator;
    void setAnnotation(cv::Vec3b color, cv::Vec3b type);
    void setAnnotation(cv::Rect object, int type);
    iterator begin(){return objects.begin();}
    iterator end(){return objects.end();}

private:

    std::string fileAddress;
    std::string fileName;

    cv::Mat mask;
    cv::Mat img;
    cv::Mat sMask;
    std::vector<bbox> objects;
    cv::Mat selects_mask;

    std::vector<goalPost> gps;
};

#endif // SAMPLE_H
