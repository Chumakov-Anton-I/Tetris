#ifndef CMAP_H
#define CMAP_H

#include <QImage>
#include <QList>

class CMap : private QImage
{
public:
    CMap(int width, int height);

    void set(const QPoint &p, QRgb color);
    inline void kill(const QPoint &p) { set(p, qRgb(0, 0, 0)); }
    bool get(const QPoint &p) const;
    QColor color(int x, int y) const { return pixelColor(x, y); }

    int searchFullLines();
    bool eraseLines();
    void reset();

private:
    QList<int> m_lines;
    CMap() {}
    CMap(CMap&&) {}
    CMap(const CMap&) : QImage() {}
};

#endif // CMAP_H
