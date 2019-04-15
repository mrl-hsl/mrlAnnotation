#include "dataset.h"

dataSet::dataSet(){

}

void dataSet::addSample(Sample _sample){
  samples.push_back(_sample);
}

Sample dataSet::getSample(int id){
  return samples[id];
}
void dataSet::setSample(int id,Sample _sample){
  samples[id] = _sample;
}

void dataSet::saveSample(int id){
//    cv::Mat result;
//    samples[id].getMask().copyTo(result);
//    for(int i=0;i<samples[id].getMask().rows;i++){
//        for(int j=0;j<samples[id].getMask().cols;j++){
//            if(samples[id].getSelectsMask().at<cv::Vec3b>(i,j)!=cv::Vec3b(0,0,0)){
//                result.at<cv::Vec3b>(i,j)=samples[id].getSelectsMask().at<cv::Vec3b>(i,j);
//            }
//        }
//    }
//    cv::imwrite(samples[id].getPath()+std::string("/")+std::string("label_")+samples[id].getName(),result);

}

int dataSet::getSize()
{
  return samples.size();
}

