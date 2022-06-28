#ifndef IGENERATORCHART_H
#define IGENERATORCHART_H

#include <QChartView>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QColor>

#include "DataElement.h"

class IGeneratorChartView
{
public:
    virtual QChartView* getChart (QList<DataElement> graphData, QList <QColor>* colors) = 0;
};

#endif // IGENERATORCHART_H

class PieChartGenerator : public IGeneratorChartView
{
    QChartView* getChart (QList<DataElement> graphData, QList <QColor>* colors)
    {
        QChartView *view = new QChartView;
        view->setRenderHint(QPainter::Antialiasing);
        QChart *chart = view->chart();
        chart->setTitle("Buetiful pie chart");
        QPieSeries *series = new QPieSeries;
        int i = 0;
           foreach (DataElement elem, graphData) {
                  // QString legend_header ();
                   series->append(elem.header, elem.val);
                   series->slices().at(i)->setBrush(colors->at(i));
                   i++;
           }
           chart->addSeries(series);

           return view;
    };
};

class BarChartGenerator : public IGeneratorChartView
{
    QChartView* getChart (QList<DataElement> graphData, QList <QColor>* colors) {

        QChartView *view = new QChartView;
        view->setRenderHint(QPainter::Antialiasing);
        QChart *chart = view->chart();
        QBarSeries *series = new QBarSeries;
        int i = 0;
        foreach (DataElement elem, graphData) {
            QBarSet *set = new QBarSet (elem.header);
            *set << elem.val;
            set->setBrush(colors->at(i));
            series->append(set);
            i++;
        }
        chart->addSeries(series);
        return view;
    };


};

