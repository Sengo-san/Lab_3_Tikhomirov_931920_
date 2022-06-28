#ifndef GRAPH_H
#define GRAPH_H

#include <QChart>
#include <QChartView>

#include <QPdfWriter>

class Graph
{
private:
    QChartView* view;
public:
    void setGraphView (QChartView* view_) {view = view_;};
    QChart* getChart () {return view->chart() ;};
    QChartView* getChartView() {return view;};
};

#endif // GRAPH_H
