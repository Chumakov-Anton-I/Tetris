#ifndef OFIGURE_H
#define OFIGURE_H

#include "Figure.h"

class OFigure : public Figure
{
public:
    OFigure(CMap *map);

    void rotate() {}
};

#endif // OFIGURE_H
