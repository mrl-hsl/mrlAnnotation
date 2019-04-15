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
  void selectPolygon(cv::Point,int);
  void selectLine(cv::Point,int);
  void selectSegment(cv::Scalar,int);
  void removeBox(cv::Point);
  void removePolygon(cv::Point);

  void fillPolygon(Polygon&,cv::Scalar);
//    inline bool inBox(cv::Point,cv::Rect);
  bool inPol(const cv::Point, Polygon);
  std::vector<bbox> objects;
  std::vector<Polygon> polygons;
  std::vector<Line> lines;
  Line tLine;
  Polygon tPolygons;
  bbox tBox;
  cv::Mat mask;
  cv::Mat drawingMask;
  cv::Mat selectionMask;

private:
  bool drawing = false;


};

#endif // SELECTORS_H
