#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <QString>
#include <QChartView>
#include "IOCContainer.h"
#include "igeneratorchart.h"
#include "igeneratorcolors.h"
#include "graph.h"
#include "iscanner.h"

class GraphGenerator
{
public:
     Graph* getGraph(DataGraph* data, QString graphType, QString coloring)
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
         if (graphType.toLower() == "barchart")
             //gContainer.RegisterFactory <IGeneratorChartView, PieChartGenerator>();
             gContainer.RegisterInstance<IGeneratorChartView, BarChartGenerator>();
         else if (graphType.toLower() == "piechart") {
             //gContainer.RegisterFactory <IGeneratorChartView, BarChartGenerator>();
             gContainer.RegisterInstance<IGeneratorChartView,PieChartGenerator>();
         }
         else
             return graph;

         //создаем установленный тип представления, раскрашенныйе установленным набором цветов
         QChartView  *view = gContainer.GetObject<IGeneratorChartView>()->getChart(
                     data->getData(),
                     gContainer.GetObject<IGeneratorColors>()->getColors(data->getElementsCount())
                     );

            graph->setGraphView(view); //селим созданное визуальное представление в график визуальное представление
           return graph;
     };
};

#endif // GRAPHGENERATOR_H
