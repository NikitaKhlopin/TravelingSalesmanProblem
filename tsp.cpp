#include "tsp.h"
#include "ui_tsp.h"
#include "top.h"
#include "edge.h"
#include <QPainter>
#include <QtMath>
#include <QIntValidator>

const int graph_R = 200;
const int shift_x = 250;
const int shift_y = 250;
const double pi = 3.1415;
const int max = 8;
bool flag[max] = {0, 0, 0, 0, 0, 0,0,0};
int count = 0;
extern QVector<TOP> tops;
extern QVector<EDGE> edges;
extern QVector<QVector<int>> map;

TSP::TSP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TSP)
{
    ui->setupUi(this);
    openGlW = new myGlWidget(this);
    ui->verticalLayout->addWidget(openGlW, 0, 0);

    ui->City1->setValidator(new QIntValidator(1,8,this));
    ui->City2->setValidator(new QIntValidator(1,8,this));
    ui->S->setValidator(new QIntValidator(1,99,this));
}

TSP::~TSP()
{
    delete ui;
}

void TSP::on_Btn_Add_Top_clicked()
{
    ui->L_Result->setText("");
    ui->L_Path_length->setText("");

    if(count != max)
    {
        int id = 0;
        while(flag[id] != 0 && id < 7)
        {
            id++;
        }
        flag[id] = 1;
        double angel = pi * 3/2 + pi * 2 / max * id;
        int knot_x = cos(angel) * graph_R + shift_x;
        int knot_y = sin(angel) * graph_R + shift_y;
        TOP top(knot_x, knot_y, id);
        tops.push_back(top);
        count++;
        QVector<int> row(count);
        row.fill(0);
        map.append(row);
        for(int i = 0; i < count - 1; i++)
        {
            map[i].append(0);
        }
        openGlW->redraw();
    }
}

void TSP::on_Btn_Add_Edge_2_clicked()
{
    ui->L_Path_length->setText("");

    if(tops.size()>1)
    {
        QString new_edge = ui->City1->text();
        int from = new_edge.toInt()-1;
        new_edge = ui->City2->text();
        int to = new_edge.toInt()-1;
        new_edge = ui->S->text();
        int weight = new_edge.toInt();

            EDGE edge(tops[from].x, tops[from].y, tops[to].x, tops[to].y, weight, 0);
            edges.push_back(edge);
            map[from][to] = weight;
            map[to][from] = weight;
            openGlW->redraw();
        }
    ui->City1->setText("");
    ui->City2->setText("");
    ui->S->setText("");
}

void TSP::on_Btn_Calculate_clicked()
{
    try
    {
        int X = 1000;
        QVector<QVector<int>> matrix = map;
        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < count; j++)
            {
                if(i==j || matrix[i][j]==0)
                {
                    matrix[i][j] = X;
                }
            }
        }
        QVector<int> from;
        QVector<int> to;
        bool calculation_flag = true;
        int sum = 0;
        while(calculation_flag)
        {

            for(int i = 0; i < count; i++)
            {
                int row_min = X;
                for(int j = 0; j < count; j++)
                {
                    row_min=qMin(row_min, matrix[i][j]);
                }
                for(int j = 0; j < count; j++)
                {
                    if(row_min != X && matrix[i][j] != X)
                    {
                        matrix[i][j] -= row_min;
                    }
                }
            }
            for(int i = 0; i < count; i++)
            {
                int column_min = X;
                for(int j = 0; j < count; j++)
                {
                    column_min=qMin(column_min, matrix[j][i]);
                }
                for(int j = 0; j < count; j++)
                {
                    if(column_min != X && matrix[j][i] != X)
                    {
                        matrix[j][i] -= column_min;
                    }
                }
            }
            int max = -1;
            int max_x;
            int max_y;
            for(int i = 0; i < count; i++)
            {
                for (int j = 0; j < count; j++)
                {
                    if(matrix[i][j] == 0)
                    {
                        int row_min = X;
                        for(int k = 0; k < count; k++)
                        {
                            if(k != j)
                            {
                                row_min = qMin(row_min, matrix[i][k]);
                            }
                        }
                        int column_min = X;
                        for(int k = 0; k < count; k++)
                        {
                            if(k != i)
                            {
                                column_min = qMin(column_min, matrix[k][j]);
                            }
                        }
                        if(row_min + column_min > max)
                        {
                            max = row_min + column_min;
                            max_x = i;
                            max_y = j;
                        }
                    }
                }
            }
            sum += map[max_x][max_y];
            matrix[max_y][max_x] = X;
            for(int i = 0; i < count; i++)
            {
                matrix[max_x][i] = X;
                matrix[i][max_y] = X;
            }
            from.push_back(max_x + 1);
            to.push_back(max_y + 1);

            calculation_flag = false;
            for(int i = 0; i < count; i++)
            {
                for(int j = 0; j < count; j++)
                {
                    if(matrix[i][j] != X)
                    {
                        calculation_flag = true;
                    }
                }
            }
        }

        QString path = QString::number(from[0]) + " --> " + QString::number(to[0]);
        int new_from = to[0];
        from.erase(from.begin());
        to.erase(to.begin());
        while(from.size() != 0)
        {
            for(int i = 0; i < from.size(); i++)
            {
                if(from[i] == new_from)
                {
                    path += " --> " + QString::number(to[i]);
                    new_from = to[i];
                    from.erase(from.begin() + i);
                    to.erase(to.begin() + i);
                }
            }
        }
        ui->L_Result->setText(path);
        QString result = "Путь = ";
        result += QString::number(sum);
        ui->L_Path_length->setText(result);
    }

    catch(...)
    {
        ui->L_Result->setText("Error");
    }

    ui->City1->setText("");
    ui->City2->setText("");
    ui->S->setText("");
}

void TSP::on_L_Clear_clicked()
{
    count=0;
    tops.clear();
    tops.squeeze();
    edges.clear();
    edges.squeeze();
    map.clear();
    map.squeeze();

    for(int i = 0; i < max; i++)
    {
        flag[i]=0;

    }
    ui->City1->setText("");
    ui->City2->setText("");
    ui->S->setText("");
    ui->L_Result->setText("");
    ui->L_Path_length->setText("");
    openGlW->redraw();
}
