#include "ichart.h"

void MyPieChart::createChart(QVector <DataElement> data)
{
    QChart *chart = chartView->chart();
    chart->setTitle("Pie Chart");
    //chart->legend()->hide();

    QPieSeries *series = new QPieSeries ();// = new QPieSeries();

    int first_n_printed = 5; //сколько первых по величине значений выведем (остальное просуммируем в "others")
    int i = 0;
    int others_count = 0;
    foreach (DataElement x, data) {
        if (i < first_n_printed){ //массив заранее отсортирован, поэтому работаем с первыми по порядку
            series->append(QString::number(x.head), x.val);
            series->slices().at(i)->setBrush(QColor(rand()%250,  rand()%250, rand()%250));
        }
        else
            others_count += x.val;
       i++;
    }

    if (i > first_n_printed)
    {series->append("Others", others_count);
    series->slices().at(first_n_printed)->setBrush(QColor(0,0,0));
    }

    chart->addSeries(series);
}
