#ifndef SELECTORS_H
#define SELECTORS_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "annotations.h"

class Selector {
public:
  Selector(){}
  ~Selector(){}

  void setStatus(bool);
  bool is_drawing();

  void selectBox(cv::Point,int);
  void selectPolygon(cv::Point,cv::Vec3b);
  void selectLine(cv::Point, cv::Vec3b, int thickness);
  void selectSegment(cv::Point,cv::Vec3b);
  void selectTreshold(cv::Vec3b);
  void removeBox(cv::Point);
  void removePolygon(cv::Point);
  void removeSegment(cv::Point, cv::Vec3b classType);
  void removeLine();
  void treshold(int minH,int minS,int minV,int maxH,int maxS, int maxV);


  void fillPolygon(Polygon&, cv::Mat mask);
//    inline bool inBox(cv::Point,cv::Rect);
  bool inPol(const cv::Point, Polygon);
  std::vector<bbox> objects;
  std::vector<Polygon> polygons;
  std::vector<Line> lines;
  Line tLine;
  Polygon tPolygons;
  bbox tBox;
  cv::Mat segmentaions;
  cv::Mat drawingMask;
  cv::Mat selectionMask;
  cv::Mat suggstedSegments;
  cv::Mat hsvImg;
  cv::Mat tresholdMask;

private:
  bool drawing = false;


};

#endif // SELECTORS_H
