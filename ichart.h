#ifndef ICHART_H
#define ICHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "ichartdata.h"
#include <QAbstractBarSeries>

class IChart //интерфейс графика
{
protected:
     //QVector <DataElement> *data; //данные графика
     QChartView *chartView;
     //QChart *chart;
public:

    virtual void createChart (QVector <DataElement>) = 0;
    QChartView* getChartView () {return chartView;}
     virtual ~IChart() {delete chartView;};
};


class MyPieChart : public IChart // конкретный тип графика
{
private:
    QPieSeries *series;
    QList <QPieSlice> *slices;
public:
    MyPieChart() {
        chartView = new QChartView;
        chartView->setRenderHint(QPainter::Antialiasing);
    };
    void createChart (QVector <DataElement>);

    ~MyPieChart() {delete series; delete slices;};
};

/*
class MyOtherChart : IChart
{

};

*/

#endif // ICHART_H
