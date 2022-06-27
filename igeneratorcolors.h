#ifndef IGENERATORCOLORS_H
#define IGENERATORCOLORS_H

#include <QColor>

class IGeneratorColors
{
public:
    virtual QList <QColor>* getColors(int colors_count) = 0;
};

class ColoredGenerator : IGeneratorColors
{
public:
    QList <QColor>* getColors(int colors_count);
};


class BWGenerator : IGeneratorColors
{
public:
    QList <QColor>* getColors(int colors_count);
};
#endif // IGENERATORCOLORS_H
