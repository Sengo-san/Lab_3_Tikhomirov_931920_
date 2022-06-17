#include "ichart.h"

int index_of_max (QVector <DataElement> data, int start = 0)
{
    int max = data.at(start).val;
    int index = start, i = 0;
    foreach (DataElement x, data){
        if (i >= start) {
            if (x.val > max){
                max = x.val;
                index = i;
            }
        }
        i++;
    }
    return index;
}

void MyPieChart::createChart(QVector <DataElement> data, int visible_amount, QList <QColor> colors)
{
    chart->setTitle(title);

    series = new QPieSeries ();

    //поместим в начало списка наибольшие элементы (для малых data.count() фактически сортируем)
    for (int z = 0; z < visible_amount && z < data.count(); z ++)
        data.push_front(data.takeAt(index_of_max(data, z)));

    int i = 0;
    int others_count = 0;
    foreach (DataElement elem, data) {
        if (i < visible_amount){ //работаем с первыми по порядку (наибольшими)
            QString legend_header ("(" + QString::number(elem.head) + "," + QString::number(elem.head + 1) + ")");
            series->append(legend_header, elem.val);
            series->slices().at(i)->setBrush(colors.at(i));
        }
        else
            others_count += elem.val;
        i++;
    }

    if (i > visible_amount) {
        series->append("Others", others_count);
        series->slices().at(visible_amount)->setBrush(QColor(colors.at(visible_amount)));
    }

    chart->removeAllSeries();
    chart->addSeries(series);
}

void MyBarChart::createChart(QVector<DataElement> data, int visible_amount, QList <QColor> colors)
{
    chart->setTitle(title);

    series = new QBarSeries();

    //поместим в начало списка наибольшие элементы (для малых data.count() фактически сортируем)
    for (int z = 0; z < visible_amount && z < data.count(); z ++)
        data.push_front(data.takeAt(index_of_max(data, z)));

    int i = 0;
    int others_count = 0;
    foreach (DataElement elem, data) {
        if (i < visible_amount){//работаем с первыми по порядку (наибольшими)
            QString legend_header ("(" + QString::number(elem.head) + "," + QString::number(elem.head + 1) + ")");
            QBarSet *set = new QBarSet(legend_header);
            *set << elem.val;
            set->setBrush(QColor(colors.at(i)));
            series->append(set);
        }
        else
            others_count += elem.val;
       i++;
    }

    if (i > visible_amount)
    {   QBarSet *set = new QBarSet("Others");
        *set << others_count;
        set->setBrush(colors.at(visible_amount));
        series->append(set);
    }

    chart->removeAllSeries();
    chart->addSeries(series);
}

void MyPieChart::recolor_chart(QList <QColor> colors)
{
    int i=0;
    foreach (QPieSlice* x, series->slices()){
        x->setBrush(colors.at(i));
        i++;
    }
}

void MyBarChart::recolor_chart(QList <QColor> colors)
{
    int i=0;
    foreach (QBarSet* x, series->barSets()){
        x->setBrush(colors.at(i));
        i++;
    }
}



