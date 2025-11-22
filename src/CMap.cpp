#include "CMap.h"

CMap::CMap(int width, int height)
    : m_width{width}, m_height(height)
{
    m_lines.reserve(4);
    m_map = new QRgb*[m_width]{};
    for (int i = 0; i< m_width; ++i)
        m_map[i] = new QRgb[m_height]{};
    reset();
}

CMap::~CMap()
{
    for (int i = 0; i < m_width; ++i)
        delete[] m_map[i];
    delete[] m_map;
}

void CMap::set(const QPoint &p, QRgb color)
{
    m_map[p.x()][p.y()] = color;
}

bool CMap::get(const QPoint &p) const
{
    if (p.x() < 0 || p.x() >= m_width || p.y() >= m_height) // avoiding index out of range
        return false;
    if (m_map[p.x()][p.y()] == qRgb(0, 0, 0))
        return true;    // cell is available
    else
        return false;   // cell is not available
}

int CMap::searchFullLines()
{
    int score = 0;
    for (int y = m_height - 1; y >= 0; --y) {   // row
        bool full = true;
        for (int x = 0; x < m_width; ++x)       // column
            full &= !get(QPoint(x, y));
        if (!full)  continue;   // skip not full rows
        ++score;
        m_lines.push_back(y);
        for (int x = 0; x < m_width; ++x)
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
        for (int x = 0; x < m_width; ++x)
            kill(QPoint(x, *ri));
    }
    // not very optimal implementation
    auto iy = m_lines.cend();
    while (iy != m_lines.cbegin()) {
        --iy;
        for (int y = *iy; y >= 0; --y) {
            int dy = y - 1;
            for (int x = 0; x < m_width; ++x) {
                QRgb color = (dy >= 0) ? getPixel(x, dy) : qRgb(0, 0, 0);
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
    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_height; ++j)
            m_map[i][j] = qRgb(0, 0, 0);
    }
}

void CMap::setPixel(int x, int y, QRgb color)
{
    m_map[x][y] = color;
}

QRgb CMap::getPixel(int x, int y)
{
    return m_map[x][y];
}
