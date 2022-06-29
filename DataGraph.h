#ifndef DATAGRAPH_H
#define DATAGRAPH_H

#include"DataElement.h"
#include <QList>

class DataGraph
{
private:
    QList <DataElement> data; //вектор заголвков и счетчиков
    int elements_count = 0;
    bool empty = 1;//пометка пустоты данных (снимется, если считываемый файл успешно открыт)

public:
    void dataGot() {empty = 0; };

    bool isEmpty() {return empty;};

    //чтобы избежать нарушения инкапсуляции data и зависимости сканнеров от DataElement, введем метод  push(QString, float)
    void push(QString header, float val) {data.push_back(DataElement(header, val)); elements_count++;};

    QList <DataElement> getData() {return data; };
    int getElementsCount () {return elements_count;}
};
#endif // DATAGRAPH_H
