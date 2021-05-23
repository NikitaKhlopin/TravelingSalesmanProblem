#include "edge.h"

EDGE::EDGE(){}
EDGE::EDGE(int X_from, int Y_from, int X_to, int Y_to, int Weight, int Type)
{
    x_f = X_from;
    y_f = Y_from;
    x_t = X_to;
    y_t = Y_to;
    weight = Weight;
    type = Type;
}
