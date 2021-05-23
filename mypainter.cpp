#include "mypainter.h"
#include "top.h"
#include "edge.h"

#include <QPainter>
#include <QPaintEvent>
#include <QtMath>

const double pi = 3.1415;
const int text_ = 16;
const int _R = 24;
const int Length = 15;
const double Angle=pi/8;

myPainter::myPainter()
{
    shape = QBrush(QColor(168, 168, 129));
    background = QBrush(QColor(235, 235, 235));
    textPen = QPen(QColor(71, 98, 68));
    glFont.setPixelSize(text_);
}

void myPainter::draw(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(),background);
    painter->setBrush(shape);
    painter->setPen(textPen);
    painter->setFont(glFont);

    extern QVector <TOP> tops;
    extern QVector <EDGE> edges;
    for (int i = 0; i < tops.size(); i++)
    {
        draw_top(tops[i].x, tops[i].y, painter, QString::number(i+1));
    }
    for (int i = 0; i < edges.size(); i++)
    {
        draw_edge(edges[i].x_f, edges[i].y_f, edges[i].x_t, edges[i].y_t, painter, edges[i].weight, edges[i].type);
    }
}

void myPainter::draw_top(int x, int y, QPainter *painter, QString name)
{
    painter->drawEllipse(QRectF(x - _R, y - _R, 2 * _R, 2 * _R));
    int text_x = x - _R / 2;
    int text_y = y - text_ / 2;
    painter->drawText(QRect(text_x, text_y, _R, text_), Qt::AlignCenter, name);
}

void myPainter::draw_edge(int x1, int y1, int x2, int y2, QPainter *painter, int weight, int type)
{
    double line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    int l_x1 = (x2 - x1) / line_length * _R + x1;
    int l_y1 = (y2 - y1) / line_length * _R + y1;
    int l_x2 = x2 - (x2 - x1) / line_length * _R;
    int l_y2 = y2 - (y2 - y1) / line_length * _R;
    painter->drawLine(l_x1, l_y1, l_x2, l_y2);
    if(type == 1)
    {
        double C;
        if (x2==l_x2 && l_y2 < y2)
        {
            C = pi * 3 / 2;
        }
        else if (x2==l_x2 && l_y2 > y2)
        {
            C = pi / 2;
        }
        else if (y2 == l_y2 && l_x2 < x2)
        {
            C = pi;
        }
        else if (y2 == l_y2 && l_x2 < x2)
        {
            C = 0;
        }
        else if (y2 < l_y2 && l_x2 < x2)
        {
            C = atan(1.0 * (y2 - l_y2) / (x2 - l_x2)) + pi;
        }
        else if (y2 > l_y2 && l_x2 < x2)
        {
            C = atan(1.0 * (y2 - l_y2) / (x2 - l_x2)) + pi;
        }
        else if (y2 < l_y2 && l_x2 > x2)
        {
            C = atan(1.0 * (y2 - l_y2) / (x2 - l_x2)) + 2 * pi;
        }
        else if (y2 > l_y2 && l_x2 > x2)
        {
            C = atan(1.0 * (y2 - l_y2) / (x2 - l_x2)) + 0;
        }
        int a_x1 = cos(C + Angle) * Length + l_x2;
        int a_x2 = cos(C - Angle) * Length + l_x2;
        int a_y1 = sin(C + Angle) * Length + l_y2;
        int a_y2 = sin(C - Angle) * Length + l_y2;
        painter->drawLine(l_x2, l_y2, a_x1, a_y1);
        painter->drawLine(l_x2, l_y2, a_x2, a_y2);
    }
    int text_x = (l_x2 + l_x1) / 2 - _R / 2;
    int text_y = (l_y2 + l_y1) / 2 - text_ / 2;
    painter->drawRect(QRectF(text_x, text_y, _R, text_));
    painter->drawText(QRect(text_x, text_y, _R, text_), Qt::AlignCenter, QString::number(weight));
}
