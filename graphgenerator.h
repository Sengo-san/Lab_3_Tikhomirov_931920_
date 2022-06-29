#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <QString>
#include <QChartView>
#include "IOCContainer.h"
#include "IGeneratorQChart.h"
#include "IGeneratorColors.h"
#include "Graph.h"
#include "IScanner.h"

class GraphGenerator
{
public:
     Graph* getGraph(DataGraph* data, QString graph_type, QString coloring)
     {
         Graph* graph = new Graph;

         if (data->isEmpty()){//проверка пометки в данных, что они собраны без ошибок
             return graph;
         }

         //настраиваем фабрики на раскраску
         if (coloring.toLower() == "colored")
             gContainer.RegisterInstance<IGeneratorColors, ColoredGenerator>();
         else if (coloring.toLower() == "bw")
             gContainer.RegisterInstance<IGeneratorColors, BWGenerator>();
         else {
             return graph;
         }

         //настраиваем фабрики на тип графика
         if (graph_type.toLower() == "barchart")
             //gContainer.RegisterFactory <IGeneratorChartView, PieChartGenerator>();
             //gContainer.RegisterInstance<IGeneratorChartView, BarChartGenerator>();
             gContainer.RegisterInstance<IGeneratorQChart, BarQChartGenerator>();
         else if (graph_type.toLower() == "piechart") {
             //gContainer.RegisterFactory <IGeneratorChartView, BarChartGenerator>();
             //gContainer.RegisterInstance<IGeneratorChartView,PieChartGenerator>();
             gContainer.RegisterInstance<IGeneratorQChart, PieQChartGenerator>();
         }
         else
             return graph;

         //создаем установленный тип представления, раскрашенныйе установленным набором цветов
         //QChartView  *view = gContainer.GetObject<IGeneratorChartView>()->getChart(
         QChart  *chart = gContainer.GetObject<IGeneratorQChart>()->getQChart(
                     data->getData(),
                     gContainer.GetObject<IGeneratorColors>()->getColors(data->getElementsCount())
                     );
            //graph->setGraphView(view); //селим созданное визуальное представление в график визуальное представление
         graph->setChart(chart);
         return graph;
     };
};

#endif // GRAPHGENERATOR_H
