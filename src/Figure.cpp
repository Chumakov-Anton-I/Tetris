#include "Figure.h"
#include "CMap.h"

Figure::Figure(CMap *map)
    : m_map{map}, m_state{true}
{
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
