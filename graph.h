#ifndef GRAPH_H
#define GRAPH_H

#include <QChart>
#include <QChartView>

#include <QPdfWriter>

class Graph
{
private:
    QChartView* view;
public:

    void setGraphView (QChartView* view_) {view = view_;};
    QChartView* getGraphView () {return view;};
    void printToPdf(QString saving_path){

        //QPdfWriter* writer = new QPdfWriter (saving_path + "/out.pdf");
        QPdfWriter writer(saving_path + "/out.pdf");
        writer.setCreator("Someone");//Указываем создателя документа
        writer.setPageSize(QPageSize::A4);//Устанавливаем размер страницы
        QPainter painter(&writer);
        view->render(&painter);
        painter.end();
    };
};

#endif // GRAPH_H
