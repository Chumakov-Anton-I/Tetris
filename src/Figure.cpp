#include "Figure.h"
#include "CMap.h"

Figure::Figure(CMap *map, Figure::Shape shape)
    : m_map{map}, m_type{shape}, m_state{true}
{
    setShape(shape);
    m_state = tryToLay(m_pos);
    if (m_state)
        fillFig();
}

void Figure::moveL()
{
    clearFig();
    // 1: try to move left
    QPoint d = m_pos - QPoint(1, 0);
    // 2: move figure (or don't)
    if (tryToLay(d))   m_pos = d;
    fillFig();
}

void Figure::moveR()
{
    clearFig();
    // 1: try to move right
    QPoint d = m_pos + QPoint(1, 0);
    // 2: move figure (or don't)
    if (tryToLay(d))
        m_pos = d;
    fillFig();
}

bool Figure::moveDown()
{
    clearFig();
    // 1: try to move down
    QPoint d = m_pos + QPoint(0, 1);
    bool can = tryToLay(d);
    // 2: move figure (or don't)
    if (can)   m_pos = d;
    fillFig();
    return can;
}

void Figure::rotate()
{
    if (m_type == Figure::ShapeO)
        return;
    for (int i = 0; i < count; ++i) {
        m_map->kill(offset[i] + m_pos);
        offset[i] = QPoint(-offset[i].y(), offset[i].x());  // rotate (x, y) --> (-y, x)
    }
    // try to layout rotated figure at current place
    if (tryToLay(m_pos)) {
        fillFig();
        return;
    }
    // try to move to left
    QPoint d = m_pos - QPoint(1, 0);
    if (tryToLay(d)) {
        m_pos = d;
        fillFig();
        return;
    }
    // try to move to right
    d = m_pos + QPoint(1, 0);
    if (tryToLay(d)) {
        m_pos = d;
        fillFig();
        return;
    }
    // can't rotate, reset
    for (int i = 0; i < count; ++i) {
        offset[i] = QPoint(offset[i].y(), -offset[i].x());  // rotate back: (x, y) --> (y, -x)
        m_map->set(offset[i] + m_pos, m_color);
    }
}

void Figure::spawn()
{
    m_state = tryToLay(m_pos);
    if (!m_state)   // couldn't create figure
        return;
    fillFig();
}

void Figure::setShape(Shape shape)
{
    switch (shape) {
    case Figure::ShapeI:
        m_pos = QPoint(4, 0);
        offset[0] = QPoint(-1, 0);
        offset[1] = QPoint( 0, 0);
        offset[2] = QPoint( 1, 0);
        offset[3] = QPoint( 2, 0);
        m_color = qRgb(255, 127, 0);    // orange
        break;
    case Figure::ShapeJ:
        m_pos = QPoint(4, 1);
        offset[0] = QPoint(-1, -1);
        offset[1] = QPoint(-1,  0);
        offset[2] = QPoint( 0,  0);
        offset[3] = QPoint( 1,  0);
        m_color = qRgb(255, 0, 255);    // magenta
        break;
    case Figure::ShapeL:
        m_pos = QPoint(4, 1);
        offset[0] = QPoint(-1,  0);
        offset[1] = QPoint( 0,  0);
        offset[2] = QPoint( 1,  0);
        offset[3] = QPoint( 1, -1);
        m_color = qRgb(0, 0, 255);    // blue
        break;
    case Figure::ShapeO:
        m_pos = QPoint(4, 0);
        offset[0] = QPoint( 0, 0);
        offset[1] = QPoint( 1, 0);
        offset[2] = QPoint( 1, 1);
        offset[3] = QPoint( 0, 1);
        m_color = qRgb(255, 0, 0);  // pure red
        break;
    case Figure::ShapeS:
        m_pos = QPoint(4, 1);
        offset[0] = QPoint(-1,  0);
        offset[1] = QPoint( 0,  0);
        offset[2] = QPoint( 0, -1);
        offset[3] = QPoint( 1, -1);
        m_color = qRgb(0, 255, 255);    // cyan
        break;
    case Figure::ShapeT:
        m_pos = QPoint(4, 1);
        offset[0] = QPoint(-1,  0);
        offset[1] = QPoint( 0,  0);
        offset[2] = QPoint( 1,  0);
        offset[3] = QPoint( 0, -1);
        m_color = qRgb(255, 255, 0);    // yellow
        break;
    case Figure::ShapeZ:
        m_pos = QPoint(4, 1);
        offset[0] = QPoint(-1, -1);
        offset[1] = QPoint( 0, -1);
        offset[2] = QPoint( 0,  0);
        offset[3] = QPoint( 1,  0);
        m_color = qRgb(0, 255, 0);    // green
        break;
    }
}

void Figure::clearFig()
{
    for (int i = 0; i < count; ++i)
        m_map->kill(offset[i] + m_pos);
}

void Figure::fillFig()
{
    for (int i = 0; i < count; ++i)
        m_map->set(offset[i] + m_pos, m_color);
}

bool Figure::tryToLay(const QPoint &pos)
{
    bool res = true;
    for (int i = 0; i < count; ++i)
        res &= m_map->get(offset[i] + pos);
    return res;
}
