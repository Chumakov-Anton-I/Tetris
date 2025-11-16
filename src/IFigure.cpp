#include "IFigure.h"
#include "CMap.h"

IFigure::IFigure(CMap *map)
    : Figure{map}
{
    m_pos = QPoint(4, 0);
    offset[0] = QPoint(-1, 0);
    offset[1] = QPoint( 0, 0);
    offset[2] = QPoint( 1, 0);
    offset[3] = QPoint( 2, 0);
    m_color = qRgb(255, 127, 0);    // orange
    spawn();
}

/*void IFigure::rotate()
{
    for (int i = 0; i < count; ++i) {
        m_map->kill(offset[i] + m_pos);
        offset[i] = offset[i].transposed();
    }
    bool can = true;
    for (int i = 0; i < count; ++i)
        can &= m_map->get(offset[i] + m_pos);
    if (can) {
        for (int i = 0; i < count; ++i)
            m_map->set(offset[i] + m_pos, m_color);
        return;
    }
    // try to move to left
    QPoint d = m_pos - QPoint(1, 0);
    can = true;
    for (int i = 0; i < count; ++i)
        can &= m_map->get(offset[i] + d);
    if (can) {
        m_pos = d;
        for (int i = 0; i < count; ++i)
            m_map->set(offset[i] + m_pos, m_color);
        return;
    }
    // try to move to right
    d = m_pos + QPoint(1, 0);
    can = true;
    for (int i = 0; i < count; ++i)
        can &= m_map->get(offset[i] + d);
    if (can) {
        m_pos = d;
        for (int i = 0; i < count; ++i)
            m_map->set(offset[i] + m_pos, m_color);
        return;
    }
    // can't rotate, reset
    for (int i = 0; i < count; ++i) {
        offset[i] = offset[i].transposed();
        m_map->set(offset[i] + m_pos, m_color);
    }
}*/
