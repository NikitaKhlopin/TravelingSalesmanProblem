#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include "mypainter.h"

class myGlWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    myGlWidget(QWidget *parent);
    void redraw();
    void paintEvent(QPaintEvent* event) override;

private:
   myPainter* mypainter;

};

#endif // MYGLWIDGET_H
