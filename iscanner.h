#ifndef ISCANNER_H
#define ISCANNER_H

//#include "datagraph.h"
//#include "iscanner.h"
//#include "DataElement.h"

#include "DataGraph.h"


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
