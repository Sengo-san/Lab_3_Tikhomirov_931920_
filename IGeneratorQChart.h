#ifndef IGENERATORQCHART_H
#define IGENERATORQCHART_H

#include <QChartView>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QColor>

#include "DataElement.h"

//class IGeneratorChartView
class IGeneratorQChart
{
public:
    //virtual QChartView* getChart (QList<DataElement> graph_data, QList <QColor>* colors) = 0;
    virtual QChart* getQChart (QList<DataElement> graph_data, QList <QColor>* colors) = 0;
};


//class PieChartGenerator : public IGeneratorChartView
class PieQChartGenerator : public IGeneratorQChart
{
    //QChartView* getChart (QList<DataElement> graph_data, QList <QColor>* colors)
    QChart* getQChart (QList<DataElement> graph_data, QList <QColor>* colors)
    {
        //QChartView *view = new QChartView;
        //QChart *chart = view->chart();
        QChart *chart = new QChart;
        //chart->setTitle("Buetiful pie chart");
        QPieSeries *series = new QPieSeries;
        int i = 0;
           foreach (DataElement elem, graph_data) {
                  // QString legend_header ();
                   series->append(elem.header, elem.val);
                   series->slices().at(i)->setBrush(colors->at(i));
                   i++;
           }
           chart->addSeries(series);

           //return view;
           return chart;
    };
};

//class BarChartGenerator : public IGeneratorChartView
class BarQChartGenerator : public IGeneratorQChart
{
    //QChartView* getChart (QList<DataElement> graph_data, QList <QColor>* colors) {
    QChart* getQChart (QList<DataElement> graph_data, QList <QColor>* colors) {
        //QChartView *view = new QChartView;
        //QChart *chart = view->chart();
        QChart *chart = new QChart;
        QBarSeries *series = new QBarSeries;
        int i = 0;
        foreach (DataElement elem, graph_data) {
            QBarSet *set = new QBarSet (elem.header);
            *set << elem.val;
            set->setBrush(colors->at(i));
            series->append(set);
            i++;
        }
        chart->addSeries(series);
        //return view;
        return chart;
    };


};


#endif // IGENERATORQCHART_H
