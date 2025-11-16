#include "SFigure.h"

SFigure::SFigure(CMap *map)
    : Figure{map}
{
    m_pos = QPoint(4, 1);
    offset[0] = QPoint(-1,  0);
    offset[1] = QPoint( 0,  0);
    offset[2] = QPoint( 0, -1);
    offset[3] = QPoint( 1, -1);
    m_color = qRgb(0, 255, 255);    // cyan
    spawn();
}

/*void SFigure::rotate()
{

}*/
