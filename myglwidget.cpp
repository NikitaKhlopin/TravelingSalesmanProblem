#include "myglwidget.h"
#include "top.h"
#include "edge.h"
#include <QPainter>

extern QVector<TOP> tops;
extern QVector<EDGE> edges;

myGlWidget::myGlWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    mypainter=new myPainter;
}

void myGlWidget::redraw()
{
   this->update();
}

void myGlWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    mypainter->draw(&painter,event);
    painter.end();
}
