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
//        mask =  cv::Mat(img.rows,img.cols,CV_8UC3,cv::Scalar(0,0,0));
    cv::cvtColor(img,img,CV_BGR2RGB);
    cv::cvtColor(sMask,sMask,CV_BGR2RGB);
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
//cv::Mat Sample::getMask(){
//    return mask;
//}
void Sample::setSMask(cv::Mat _sMask){
  sMask = _sMask;
}

cv::Mat Sample::getSMask(){
  return sMask;
}

std::string Sample::getName(){
  return fileName;
}

std::string Sample::getPath(){
  return fileAddress;
}

