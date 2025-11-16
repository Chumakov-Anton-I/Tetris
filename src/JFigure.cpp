#include "JFigure.h"

JFigure::JFigure(CMap *map)
    : Figure{map}
{
    m_pos = QPoint(4, 1);
    offset[0] = QPoint(-1, -1);
    offset[1] = QPoint(-1,  0);
    offset[2] = QPoint( 0,  0);
    offset[3] = QPoint( 1,  0);
    m_color = qRgb(255, 0, 255);    // magenta
    spawn();
}

/*void JFigure::rotate()
{

}*/
