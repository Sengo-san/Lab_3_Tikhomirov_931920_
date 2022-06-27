#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <QString>
#include <graph.h>
#include <datagraph.h>
#include <QChartView>

#include "IOCContainer.h"
#include "igeneratorchart.h"
#include "igeneratorcolors.h"



class GraphGenerator
{
public:
     Graph* getGraph(DataGraph* data, QString graphType, QString coloring)
     {
         Graph* graph = new Graph;

         if (data->isEmpty()) {
             return graph;
         }

         //настраиваем фабрики на раскраску
         if (coloring.toLower() == "colored")
             gContainer.RegisterInstance<IGeneratorColors, ColoredGenerator>();
         else if (coloring.toLower() == "bw")
             gContainer.RegisterInstance<IGeneratorColors, BWGenerator>();
         else
             return graph;

         //настраиваем фабрики на тип графика
         if (graphType.toLower() == "barchart")
             gContainer.RegisterInstance<IGeneratorChartView, PieChartGenerator>();

         else if (graphType.toLower() == "piechart")
             gContainer.RegisterInstance<IGeneratorChartView, PieChartGenerator>();
         else
             return graph;

         //создаем установленное представление, раскрашеное установленным набором цветов
         QChartView  *view = gContainer.GetObject<IGeneratorChartView>()
                 ->getChart(data->getData(), gContainer.GetObject<IGeneratorColors>()->getColors(data->getElementsCount()));

           graph->setGraphView(view); //ставим конкретное визуальное представление
           return graph;
     };
};

#endif // GRAPHGENERATOR_H
