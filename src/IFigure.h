#ifndef IFIGURE_H
#define IFIGURE_H

#include "Figure.h"

class IFigure : public Figure
{
public:
    IFigure(CMap *map);

    //void rotate();
};

#endif // IFIGURE_H
