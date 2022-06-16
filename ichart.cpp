#include "ichart.h"

void MyPieChart::createChart(QVector <DataElement> data, int visible_amount)
{
    //QChart *chart = chartView->chart();
    chart->setTitle("Pie Chart");

    QPieSeries *series = new QPieSeries ();

    int i = 0;
    int others_count = 0;
    foreach (DataElement elem, data) {
        if (i < visible_amount){ //массив заранее отсортирован, поэтому работаем с первыми по порядку
            QString legend_header ("(" + QString::number(elem.head) + "," + QString::number(elem.head + 1) + ")");
            series->append(legend_header, elem.val);
            series->slices().at(i)->setBrush(QColor(rand()%250,  rand()%250, rand()%250));
        }
        else
            others_count += elem.val;
       i++;
    }

    if (i > visible_amount)
    {series->append("Others", others_count);
    series->slices().at(visible_amount)->setBrush(QColor(0,0,0));
    }

    chart->removeAllSeries();
    chart->addSeries(series);
}


void MyBarChart::createChart(QVector<DataElement> data, int visible_amount)
{
   // QChart *chart = chartView->chart();
    chart->setTitle("Bar chart");

    QBarSeries *series = new QBarSeries();

    int i = 0;
    int others_count = 0;
    foreach (DataElement elem, data) {
        if (i < visible_amount){//массив заранее отсортирован, поэтому работаем с первыми по порядку
            QString legend_header ("(" + QString::number(elem.head) + "," + QString::number(elem.head + 1) + ")");
            QBarSet *set = new QBarSet(legend_header);
            *set << elem.val;
            set->setBrush(QColor(rand()%250,  rand()%250, rand()%250));
            series->append(set);
        }
        else
            others_count += elem.val;
       i++;
    }

    if (i > visible_amount)
    {   QBarSet *set = new QBarSet("Others");
        *set << others_count;
        set->setBrush(QColor(0,0,0));
        series->append(set);
    }

    chart->removeAllSeries();
    chart->addSeries(series);
}
