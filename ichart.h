#ifndef ICHART_H
#define ICHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "ichartdata.h"
#include <QAbstractBarSeries>
#include <QJsonDocument>
#include <QBarSeries>
#include <QBarSet>

class IChart //интерфейс графика
{

public:
    virtual void createChart (QVector <DataElement>, int visible_amount, QList <QColor> colors) = 0; //функция построения графика. конкретная реализация - в конкретном графике
    //visible_amount - количество выведеных значений (первых по величине), остальное суммируется в "others"
    virtual void recolor_chart (QList <QColor>) = 0; //перекрасить цветами списка
    virtual QChart* getChart() = 0;
    virtual ~IChart() {};
};


class MyPieChart : public IChart // конкретный тип графика
{
protected:
    QChart *chart;
    QPieSeries *series;
public:
    MyPieChart() {
        chart = new QChart;
    };
    QChart* getChart() {return chart;};
    void createChart (QVector <DataElement>, int visible_amount, QList <QColor> colors);
    void recolor_chart (QList <QColor>);
    ~MyPieChart() {
       // delete chart;
    };
};


class MyBarChart : public IChart // конкретный тип графика
{
protected:
    QChart *chart;
    QBarSeries *series;
    //QChartView *chartView;
public:
    MyBarChart() {
    chart = new QChart;
    };
     QChart* getChart() {return chart;};
    void createChart (QVector <DataElement>, int visible_amount, QList <QColor> colors);
    void recolor_chart (QList <QColor>);
    ~MyBarChart() {
        //delete chart;
      };
};


#endif // ICHART_H
