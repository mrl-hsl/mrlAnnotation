#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct ball{
    int radius;
    cv::Point center;
};
struct goalPost{
    std::vector<cv::Point> points;
};
struct bbox{
    cv::Point tl,br;
};
struct robot{
    bbox bBox;
};
struct landMarks{
    bbox bBox;
    int type;
};

struct fieldBoundary{
    std::vector<cv::Point> points;
};

class sample{

public:

    sample(std::string address,std::string name):fileAddress(address),fileName(name){}
    sample();
    void imRead();

    void setSMask(cv::Mat _sMask);
    void addSegment(cv::Vec3b color,cv::Vec3b type);
    void removeSegment(cv::Vec3b color);

    cv::Mat getImg();
    cv::Mat getMask();
    cv::Mat getSMask();
    cv::Mat getSelectsMask();
    std::string getName();
    std::string getPath();


private:

    std::string fileAddress;
    std::string fileName;

    fieldBoundary fb;
    cv::Mat mask;
    cv::Mat selects_mask;
    cv::Mat img;
    cv::Mat sMask;

    std::vector<ball> balls;
    std::vector<robot> robots;
    std::vector<landMarks> lms;
    std::vector<goalPost> gps;
};

#endif // SAMPLE_H
