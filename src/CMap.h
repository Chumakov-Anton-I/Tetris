#ifndef CMAP_H
#define CMAP_H

#include <QPoint>
#include <QColor>
#include <QList>

class CMap
{
public:
    CMap(int width, int height);
    ~CMap();

    bool get(const QPoint &p) const;
    void set(const QPoint &p, QRgb color);
    inline void kill(const QPoint &p) { set(p, qRgb(0, 0, 0)); }
    QColor color(int x, int y) { return QColor(getPixel(x, y)); }

    int searchFullLines();
    bool eraseLines();
    void reset();

private:
    int m_width;
    int m_height;
    QRgb **m_map;
    QList<int> m_lines;

    void setPixel(int x, int y, QRgb color);
    QRgb getPixel(int x, int y);
    CMap() {}
    CMap(CMap&&) {}
    CMap(const CMap&) {}
};

#endif // CMAP_H
