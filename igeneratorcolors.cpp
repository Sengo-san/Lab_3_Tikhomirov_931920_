#include "IGeneratorColors.h"

QList <QColor>* ColoredGenerator::getColors(int colors_count)
{
    QList <QColor>* colors = new QList <QColor>;

    for (int i = 0; i < colors_count; i++){
        int r = rand()%250;
        int g = rand()%250;
        int b = rand()%250;
        colors->push_back(QColor(r,g,b)); //добавляем случайный цвет
    }
    return colors;
};

QList <QColor>* BWGenerator::getColors(int colors_count)
{
    QList <QColor>* colors = new QList <QColor>;

    for (int i = 0; i < colors_count; i++){
        int r = rand()%255;
        colors->push_back(QColor(r, r, r)); //получаем случайный оттенок серого
    }
    return colors;
};
