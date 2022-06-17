#ifndef ICHART_H
#define ICHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QAbstractBarSeries>
#include <QJsonDocument>
#include <QBarSeries>
#include <QBarSet>

#include "ichartdata.h"

class IChart //интерфейс графика
{
public:
    QString title;
    //функция построения графика. конкретная реализация - в конкретном графике.
    //аргументы: отсортированный вектор данных, число видимых на графике элементов, цвета раскраски, заголовок
    virtual void createChart (QVector <DataElement>, int visible_amount, QList <QColor> colors) = 0;

    //visible_amount - количество выведеных значений (первых по величине), остальное суммируется в "others"
    virtual void recolor_chart (QList <QColor>) = 0; //перекрасить цветами списка
    virtual QChart* getChart() = 0;
    virtual ~IChart() {};
};

class MyPieChart : public IChart // конкретный тип графика
{
protected:
    //QString title;
    QChart *chart;
    QPieSeries *series;
public:
    MyPieChart() {
        title = "Pie chart";
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
    //QString title;
    QChart *chart;
    QBarSeries *series;
    //QChartView *chartView;
public:
    MyBarChart() {
        title = "Bar chart";
        chart = new QChart;
    };
     QChart* getChart() {return chart;};
    void createChart (QVector <DataElement>, int visible_amount, QList <QColor> colors);
    void recolor_chart (QList <QColor>);
    ~MyBarChart() {
        //delete chart;
      };
};

int index_of_max (QVector <DataElement> data, int start); //поиск индекса макс. (по DataElement::val) элемента

#endif // ICHART_H
