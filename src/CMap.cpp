#include "CMap.h"

CMap::CMap(int width, int height)
    : QImage(width, height, QImage::Format_ARGB32_Premultiplied)
{
    m_lines.reserve(4);
    fill(qRgb(0, 0, 0));
}

void CMap::set(const QPoint &p, QRgb color)
{
    setPixel(p.x(), p.y(), color);
}

bool CMap::get(const QPoint &p) const
{
    if (p.x() < 0 || p.x() >= width() || p.y() >= height()) // avoiding index out of range
        return false;
    if (pixel(p) == qRgb(0, 0, 0))
        return true;    // cell is available
    else
        return false;   // cell is not available
}

int CMap::searchFullLines()
{
    int score = 0;
    for (int y = height() - 1; y >= 0; --y) {   // row
        bool full = true;
        for (int x = 0; x < width(); ++x)       // column
            full &= !get(QPoint(x, y));
        if (!full)  continue;   // skip not full rows
        ++score;
        m_lines.push_back(y);
        for (int x = 0; x < width(); ++x)
            setPixel(x, y, qRgb(255, 255, 255));    // highlight full row
    }
    return score;
}

bool CMap::eraseLines()
{
    if (m_lines.isEmpty())
        return false;
    // clear highlighting
    for (auto ri = m_lines.cbegin(); ri != m_lines.cend(); ++ri) {
        for (int x = 0; x < width(); ++x)
            kill(QPoint(x, *ri));
    }
    // not very optimal implementation
    auto iy = m_lines.cend();
    while (iy != m_lines.cbegin()) {
        --iy;
        for (int y = *iy; y >= 0; --y) {
            int dy = y - 1;
            for (int x = 0; x < width(); ++x) {
                QRgb color = (dy >= 0) ? pixel(x, dy) : qRgb(0, 0, 0);
                setPixel(x, y, color);
            }
        }
    }
    m_lines.clear();    // clear list of erased rows
    return true;
}

void CMap::reset()
{
    m_lines.clear();
    fill(qRgb(0, 0, 0));
}
