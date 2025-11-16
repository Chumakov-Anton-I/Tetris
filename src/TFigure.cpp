#include "TFigure.h"

TFigure::TFigure(CMap *map)
    : Figure{map}
{
    m_pos = QPoint(4, 1);
    offset[0] = QPoint(-1,  0);
    offset[1] = QPoint( 0,  0);
    offset[2] = QPoint( 1,  0);
    offset[3] = QPoint( 0, -1);
    m_color = qRgb(255, 255, 0);    // yellow
    spawn();
}

/*void TFigure::rotate()
{

}*/
