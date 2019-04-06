#include "selector.h"

void Selector::setStatus(bool a){
    drawing = a;
}
bool Selector::is_drawing(){
    return drawing;
}

void Selector::selectBox(cv::Point point, int type){
    if(drawing){
        tBox.box.width = point.x - tBox.box.x;
        tBox.box.height = point.y - tBox.box.y;
        tBox.type = type;
        objects.push_back(tBox);
        drawing = false;
    }else{
        tBox.box.x = point.x;
        tBox.box.y = point.y;
        drawing = true;
    }
}

void Selector::selectPolygon(cv::Point point, int type){
    if(drawing){
        if(cv::norm(*tPolygons.begin()-point)<10){
            tPolygons.push(point);
            tPolygons.type = type;
            drawing = false;
        }else{
            tPolygons.push(point);
        }
    }else{
        tPolygons.push(point);
        drawing = true;
    }

}

void Selector::selectLine(cv::Point point, int type){
    if(drawing){
        tLine.p2 = point;
        lines.push_back(tLine);
        tLine.type = type;
        drawing = false;
    }else{
        tLine.p1 = point;
        drawing = true;
    }
}
inline bool Selector::inBox(cv::Point point, cv::Rect rect){
    return (point.x > rect.x && point.x < rect.x+rect.width && point.y > rect.y && point.y < rect.y+rect.height);
}
void Selector::removeBox(cv::Point point){
    //Posibel seg fult
    for(std::vector<bbox>::iterator box = objects.begin();box<objects.end();box++){
        if(inBox(point,box->box)){
            objects.erase(box);
            break;
        }
    }
}
