#ifndef GRAPH_H
#define GRAPH_H

#include <QChart>
#include <QChartView>

class Graph
{
private:
    QChart* chart;
public:
    QChart* getChart () {return chart;};
    void setChart (QChart* chart_) {chart = chart_;};
};


#endif // GRAPH_H
