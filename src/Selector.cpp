#include "selector.h"
#include "iostream"
void Selector::setStatus(bool a){
  drawing = a;
}

bool Selector::is_drawing(){
  return drawing;
}

void Selector::selectBox(cv::Point point, int type){
  if(drawing){
    tBox.box = cv::Rect(tBox.box.tl(),point);
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
      tPolygons.push(*tPolygons.begin());
      tPolygons.type = type;
      drawing = false;
      polygons.push_back(tPolygons);
      tPolygons.clear();
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

void Selector::removeBox(cv::Point point){
  if(drawing){
    drawing = false;
    return;
  }
  for(std::vector<bbox>::iterator box = objects.begin(); box < objects.end();box++){
    if(box->box.contains(point)){
      objects.erase(box);
    }
  }
}

bool Selector::inPol(const cv::Point in_PT,Polygon in_Pol){
  double slope ,INT_W;
  int R_hand=0;
  for(Polygon::iterator vert_it = in_Pol.points.begin();vert_it+1 < in_Pol.points.end();vert_it++){
    if(vert_it->x-(vert_it+1)->x != 0){
      slope=(float)(((vert_it+1)->y-vert_it->y)/(float)(vert_it->x-(vert_it+1)->x));
      if(slope != 0){
        INT_W=((float)(vert_it->y-in_PT.y)/slope)+(float)vert_it->x;
        if((vert_it->x < INT_W && (vert_it+1)->x > INT_W )||
           (vert_it->x > INT_W && (vert_it+1)->x < INT_W)){
          if(INT_W > in_PT.x){
            R_hand++;
          }
        }
      }
    }
    else if((vert_it->y<=in_PT.y && (vert_it+1)->y>=in_PT.y) || (vert_it->y>=in_PT.y && (vert_it+1)->y<=in_PT.y)){
      INT_W=vert_it->x;
      if(in_PT.x<INT_W)
        R_hand++;
    }
  }
  return (R_hand%2 !=0);
}

void Selector::removePolygon(cv::Point in_P){
  if(drawing){
    drawing = false;
    tPolygons.clear();
    return;
  }
  for(std::vector<Polygon>::iterator pol_it=polygons.begin();pol_it<polygons.end();pol_it++){
    if(inPol(in_P,*pol_it)){
      polygons.erase(pol_it);
    }
  }
}

void Selector::fillPolygon(Polygon &polygon,cv::Scalar classType){
    // TODO add support for non convex polygons
    cv::fillConvexPoly(selectionMask,polygon.points,classType);
}
