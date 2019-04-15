#include "Sample.h"
#include "iostream"

Sample::Sample(){

}
void Sample::imRead(){
  if(img.empty()){
    std::cout<<fileAddress+std::string("/")+fileName;
    img = cv::imread(fileAddress+std::string("/")+fileName);
    cv::resize(img,img,cv::Size(640,480));
    sMask = cv::Mat(img.rows,img.cols,CV_8UC3,cv::Scalar(0,0,0));
    selectionMask = cv::Mat(img.rows,img.cols,CV_8UC3,cv::Scalar(0,0,0));
    drawingMask = cv::Mat(img.rows,img.cols,CV_8UC3,cv::Scalar(0,0,0));
    img.copyTo(suggstedSegments);
    cv::cvtColor(img,img,CV_BGR2RGB);
    cv::cvtColor(suggstedSegments,suggstedSegments,CV_BGR2RGB);
    }
}


//void Sample::removeSegment(cv::Vec3b color){
//    for(int i = 0;i < img.rows;i++){
//        for(int j=0;j<img.cols;j++){
//            if(sMask.at<cv::Vec3b>(i,j) == color){
//                mask.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
//            }
//        }
//    }
//}

cv::Mat Sample::getImg(){
  return img;
}

void Sample::setSMask(cv::Mat _sMask){
    sMask = _sMask;
}

void Sample::suggestSegments(EGBS &segmentor,int k,int v){
    segmentor.applySegmentation(suggstedSegments,k,v);
}

void Sample::generateMask(){
    img.copyTo(segmentaions);
    for(int i = 0;i < drawingMask.rows;i++){
        for(int j=0;j<drawingMask.cols;j++){
            if(drawingMask.at<cv::Vec3b>(i,j) != cv::Vec3b(0,0,0) ){
                segmentaions.at<cv::Vec3b>(i,j) = drawingMask.at<cv::Vec3b>(i,j);
            }
        }
    }
}
cv::Mat Sample::getSMask(){
  return suggstedSegments;
}

std::string Sample::getName(){
  return fileName;
}

std::string Sample::getPath(){
  return fileAddress;
}

