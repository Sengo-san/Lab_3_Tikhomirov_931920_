#ifndef ISCANNER_H
#define ISCANNER_H

#include <QString>

#include "datagraph.h"

class IScanner
{
public:
    virtual DataGraph* getData(QString source_path)  = 0;
};

class SqliteScanner : IScanner
{
    DataGraph* getData(QString source_path);
};


class JsonScanner : IScanner
{
    DataGraph* getData(QString source_path);
};

#endif // ISCANNER_H
