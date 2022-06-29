#ifndef DATAELEMENT_H
#define DATAELEMENT_H

#include <QString>

struct DataElement //элемент данных
{
public:
    QString header;
    float val;
    DataElement (QString header_, float val_)
    {
        header = header_;
        val = val_;
    } ;
};


#endif // DATAELEMENT_H
