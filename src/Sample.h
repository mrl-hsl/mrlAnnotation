#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "selector.h"
#include "EGBS.h"

class Sample : public Selector{

public:
  Sample(std::string address,std::string name):fileAddress(address),fileName(name){}
  Sample();
  void imRead();

  void setSMask(cv::Mat _sMask);
  void suggestSegments(EGBS& segmentor,int k,int v);

  cv::Mat getImg();
  cv::Mat getMask();
  cv::Mat getSMask();
  void generateMask(cv::Mat &);
  void generateMask();
  void save(const char * add);
  void reversTreshoding();


  std::string getName();
  std::string getPath();



private:

  std::string fileAddress;
  std::string fileName;
  cv::Mat img;
  cv::Mat sMask;
};

#endif // SAMPLE_H
