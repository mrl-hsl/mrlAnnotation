#ifndef MQLABEL_H
#define MQLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class mqlabel : public QLabel
{
    Q_OBJECT
public:
    explicit mqlabel(QWidget *parent= 0);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    int x,y;
    bool left;

signals:
    void mousePressed();
    void mousePos();
};

#endif // MQLABEL_H
