#include "mqlabel.h"

mqlabel::mqlabel(QWidget * parent) : QLabel(parent)
{

}

void mqlabel::mousePressEvent(QMouseEvent *ev){
  if(ev->button()==Qt::LeftButton)
    left = true;
  else
    left = false;
  emit mousePressed();

}

void mqlabel::mouseMoveEvent(QMouseEvent *ev){
  x = ev->x();
  y = ev->y();
  pos.x = int(ev->x());
  pos.y = int(ev->y());
  emit mousePos();
}
