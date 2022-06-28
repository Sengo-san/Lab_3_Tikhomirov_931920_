#ifndef ISCANNER_H
#define ISCANNER_H

//#include "datagraph.h"
//#include "iscanner.h"
#include <QList>
#include "DataElement.h"


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

class IScanner
{
public:
    virtual DataGraph* getData(QString source_path)  = 0;
};

class SqliteScanner : public IScanner
{
    DataGraph* getData(QString source_path);
};


class JsonScanner : public IScanner
{
    DataGraph* getData(QString source_path);
};

#endif // ISCANNER_H
