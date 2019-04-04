#include "polygon.h"

Polygon::~Polygon(){
}
void Polygon::add_vertex(cv::Point2d pt){
    vertices.push_back(pt);
}
void Polygon::remove_vertex(int num){
    for(int i=0;i<num;i++)
        if(vertices.size()!=0)
            vertices.pop_back();
}
void Polygon::draw(cv::Mat * img,cv::Vec3b color){
    cv::Point2d p_buf;
    int LeftHand,RightHand;
    int is_v=-1;
    bounds.push_back(vertices[0]);
    for(int i=0;i<int(vertices.size());i++){
        if(i!=int(vertices.size())-1){
            is_v=-2;
            cv::LineIterator It(*img,vertices[i],vertices[i+1]);
            if((vertices[i+1].y<vertices[i].y && vertices[abs(i-1)].y<vertices[i].y) ||
               (vertices[i+1].y>vertices[i].y && vertices[abs(i-1)].y>vertices[i].y)     ){
                p_buf=bounds[bounds.size()-1];
                bounds.pop_back();
                It++;
                while(It.pos().y==p_buf.y){
                    It++;
                    is_v-=1;
                }
                bounds.push_back(It.pos());
            }
            else{
                is_v=-1;
            }
            It++;
            for(int j=0;j<It.count+is_v;j++,It++){
                if(bounds[bounds.size()-1].y!=It.pos().y)
                    bounds.push_back(It.pos());
            }
        }
        else{
            is_v=-2;
            cv::LineIterator It(*img,vertices[i],vertices[0]);
            if((vertices[0].y<vertices[i].y && vertices[abs(i-1)].y<vertices[i].y) ||
               (vertices[0].y>vertices[i].y && vertices[abs(i-1)].y>vertices[i].y)  ){
                    p_buf=bounds[bounds.size()-1];
                    bounds.pop_back();
                    It++;
                    while(It.pos().y==p_buf.y){
                        It++;
                        is_v-=1;
                    }
                    bounds.push_back(It.pos());
            }
            else{
                is_v=-1;
            }
            It++;
            for(int j=0;j<It.count+is_v;j++,It++){
                if(bounds[bounds.size()-1].y!=It.pos().y)
                    bounds.push_back(It.pos());
            }
            if((vertices[0].y<vertices[1].y && vertices[0].y<vertices[vertices.size()-1].y) ||
               (vertices[0].y>vertices[1].y && vertices[0].y>vertices[vertices.size()-1].y))
                bounds.pop_back();
        }
        if(vertices[i].x>X_Max)
            X_Max=vertices[i].x;
        if(vertices[i].x<X_Min)
            X_Min=vertices[i].x;
        if(vertices[i].y>Y_Max)
            Y_Max=vertices[i].y;
        if(vertices[i].y<Y_Min)
            Y_Min=vertices[i].y;
    }

    for(int i=Y_Min;i<Y_Max;i++){
        for(int j=X_Min;j<X_Max;j++){
            RightHand=0;
            LeftHand =0;
            for(int k=0;k<int(bounds.size());k++){
                if(bounds[k].y==i){
                    if(bounds[k].x<j)
                        LeftHand++;
                    else if(bounds[k].x>j)
                        RightHand++;
                }
            }
            if(LeftHand%2!=0 && RightHand%2!=0)
                pts.push_back(cv::Point2d(j,i));
        }
    }
    for(int i=0;i<int(pts.size());i++){
        img->at<cv::Vec3b>(pts[i].y,pts[i].x)=color;
    }
//    for(int i=0;i<bounds.size();i++)
//        img->at<cv::Vec3b>(bounds[i].y,bounds[i].x)=color;
}
std::vector<cv::Point2d> Polygon::get_points(){
    return pts;
}
std::vector<cv::Point2d> Polygon::get_vertices(){
    return vertices;
}
std::vector<cv::Point2d> Polygon::get_bounds(){
    return bounds;
}
void Polygon::clean(cv::Mat *M){
    for(int i=0;i<int(pts.size());i++){
        M->at<cv::Vec3b>(pts[i].y,pts[i].x)=0;
    }
}
