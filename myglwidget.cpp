#include "myglwidget.h"
#include "mypainter.h"
#include <QPainter>
#include<vector>

myGLWidget::myGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    mypainter=new myPainter;
}
void myGLWidget::redraw()
{
    //mypainter->front.setColor((QColor(255,0,0)));
    this->update();
}
void myGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    mypainter->draw(&painter,event);
    painter.end();

}
