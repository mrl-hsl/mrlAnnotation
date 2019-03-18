#include "line.h"

void Line::draw(cv::Mat *M ,cv::Scalar S,int Thickness){
    thickness=Thickness;
    color=S;
    cv::line(*M,Pt1,Pt2,S,Thickness);
}
void Line::clean(cv::Mat* M){
    cv::line(*M,Pt1,Pt2,cv::Scalar(0,0,0),thickness);
}
void Line::is_drawing(bool a){
    drawing = a;
}
bool Line::is_drawing(){
    return drawing;
}
void Line::set_thickness(int T){
    thickness=T;
}
int Line::get_thickness(){
    return thickness;
}
void Line::set_point1(cv::Point2d P){
    Pt1=P;
}
void Line::set_point2(cv::Point2d P){
    Pt2=P;
}
cv::Point2d Line::get_point1(){
    return Pt1;
}
cv::Point2d Line::get_point2(){
    return Pt2;
}
cv::Scalar Line::get_color(){
    return color;
}
