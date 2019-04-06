#include "sample.h"
#include "iostream"

sample::sample(){

}
void sample::imRead(){
    if(img.empty()){
        std::cout<<fileAddress+std::string("/")+fileName;
        img = cv::imread(fileAddress+std::string("/")+fileName);
        cv::resize(img,img,cv::Size(640,480));
        sMask = cv::Mat(img.rows,img.cols,CV_8UC3,cv::Scalar(0,0,0));
        mask =  cv::Mat(img.rows,img.cols,CV_8UC3,cv::Scalar(0,0,0));
        selects_mask = cv::Mat(img.rows,img.cols,CV_8UC3,cv::Scalar(0,0,0));
        cv::cvtColor(img,img,CV_BGR2RGB);
        cv::cvtColor(sMask,sMask,CV_BGR2RGB);
        cv::cvtColor(selects_mask,selects_mask,CV_BGR2RGB);
    }
}

void sample::setAnnotation(cv::Vec3b color, cv::Vec3b type){
    for(int i = 0;i < img.rows;i++){
        for(int j=0;j<img.cols;j++){
            if(sMask.at<cv::Vec3b>(i,j) == color){
                mask.at<cv::Vec3b>(i,j) = type;
            }
        }
    }
}
void sample::setAnnotation(cv::Rect object, int type){
    bbox a(object,type);
    objects.push_back(a);
}

void sample::removeSegment(cv::Vec3b color){
    for(int i = 0;i < img.rows;i++){
        for(int j=0;j<img.cols;j++){
            if(sMask.at<cv::Vec3b>(i,j) == color){
                mask.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
            }
        }
    }
}

cv::Mat sample::getImg(){
    return img;
}
cv::Mat sample::getMask(){
    return mask;
}
void sample::setSMask(cv::Mat _sMask){
    sMask = _sMask;
}

cv::Mat sample::getSMask(){
    return sMask;
}

std::string sample::getName()
{
    return fileName;
}

std::string sample::getPath()
{
    return fileAddress;
}
cv::Mat sample::getSelectsMask(){
    return selects_mask;
}
