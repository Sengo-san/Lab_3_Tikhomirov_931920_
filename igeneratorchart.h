#ifndef IGENERATORCHART_H
#define IGENERATORCHART_H

#include <QChartView>
#include "DataElement.h"
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QColor>

class IGeneratorChartView
{
public:
    virtual QChartView* getChart (QList<DataElement> graphData, QList <QColor>* colors) = 0;
};

#endif // IGENERATORCHART_H

class PieChartGenerator : IGeneratorChartView
{
    QChartView* getChart (QList<DataElement> graphData, QList <QColor>* colors)
    {
        QChartView *view = new QChartView;
        QChart *chart = view->chart();
        chart->setTitle("Buetiful pie chart");
        QPieSeries series;
        int i = 0;
           foreach (DataElement elem, graphData) {
                  // QString legend_header ();
                   series.append(elem.header, elem.val);
                   series.slices().at(i)->setBrush(colors->at(i));
                   i++;
           }
           chart->addSeries(&series);
           return view;
    };
};

class BarChartGenerator : IGeneratorChartView
{
    QChartView* getChart (QList<DataElement> graphData, QList <QColor>* colors) {

        QChartView *view = new QChartView;
        QChart *chart = view->chart();
        QBarSeries series;
        int i = 0;
        foreach (DataElement elem, graphData) {
            //QString legend_header ("(" + QString::number(elem.head) + "," + QString::number(elem.head + 1) + ")");
            QBarSet *set = new QBarSet (elem.header);
            *set << elem.val;
            set->setBrush(colors->at(i));
            series.append(set);
            i++;
        }
        chart->addSeries(&series);
        return view;
    };


};

