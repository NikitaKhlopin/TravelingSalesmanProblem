#ifndef EDGE_H
#define EDGE_H


class EDGE
{
public:
    EDGE();
    EDGE(int X_from, int Y_from, int X_to, int Y_to, int Weight, int Type);

public:
    int x_f,y_f, x_t,y_t,weight,type;
};

#endif // EDGE_H
