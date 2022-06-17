#ifndef ICHARTDATA_H
#define ICHARTDATA_H

#include <QtSql>
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

struct DataElement //пара заголовок-значение
{
public:
    int head;
    int val;
    DataElement (int head_, int val_) { head = head_; val = val_; };
};

bool operator== (const DataElement x, const DataElement y);
bool operator!= (const DataElement x, const DataElement y);


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
