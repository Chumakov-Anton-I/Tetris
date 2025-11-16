#include "OFigure.h"

OFigure::OFigure(CMap *map)
    : Figure{map}
{
    m_pos = QPoint(4, 0);
    offset[0] = QPoint( 0, 0);
    offset[1] = QPoint( 1, 0);
    offset[2] = QPoint( 1, 1);
    offset[3] = QPoint( 0, 1);
    m_color = qRgb(255, 0, 0);  // pure red
    spawn();
}

