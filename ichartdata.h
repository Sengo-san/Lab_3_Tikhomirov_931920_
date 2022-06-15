#ifndef ICHARTDATA_H
#define ICHARTDATA_H

#include <QtSql>
#include <QString>

struct DataElement //пара заголовок-значение
{
public:
    int head;
    int val;
    DataElement (int head_, int val_) { head = head_; val = val_; };
};


class IChartData //интерфейс получения данных из разных источников
{
public:
    virtual QVector <DataElement> getData (QString path_) = 0; // собирает данные "сколько значений попало в целочисленный интервал (i, i+1)"
};

class ChartDataSqlite : public IChartData //для Sqlite-файлов
{
public:
    QVector <DataElement> getData (QString path_);
};

class ChartDataJson: public IChartData //для Json-файлов
{
public:
    QVector <DataElement> getData (QString path_);
};
#endif // ICHARTDATA_H
