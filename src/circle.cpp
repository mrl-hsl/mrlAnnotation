#include "circle.h"
Circle::Circle(){}
Circle::Circle(int Rad,cv::Point2d Cen){
    radius=Rad;
    centre=Cen;
}
void Circle::set_radius(int R){
    radius=R;
}
void Circle::set_centre(cv::Point2d P){
    centre=P;
}
void Circle::draw(cv::Mat * img, cv::Vec3b color,int thickness){
    cv::circle(*img,centre,radius,color,thickness);
}
int Circle::get_radius(){
    return radius;
}
cv::Point2d Circle::get_centre(){
    return centre;
}
void Circle::clean(cv::Mat * M){
    cv::circle(*M,centre,radius,cv::Scalar(0,0,0),-1);
}
void Circle::Fill(){
    for(int i=centre.x;i<radius;i++){

    }
}
