#ifndef FIGURE_H
#define FIGURE_H

#include <QPoint>
#include <QColor>

class CMap;

class Figure
{
public:
    enum Shape {
        ShapeI,
        ShapeJ,
        ShapeL,
        ShapeO,
        ShapeS,
        ShapeT,
        ShapeZ,
        UndefinedShape
    };
    Figure(CMap *map);
    virtual ~Figure() {}

    void moveL();
    void moveR();
    bool moveDown();
    virtual void rotate();

    bool isValid() const { return m_state; };

protected:
    void spawn();
    Figure::Shape m_type;
    CMap *m_map;
    static const int count = 4;
    QPoint m_pos;
    QPoint offset[count];
    QRgb m_color;
    bool m_state;

    void clearFig();
    void fillFig();
    bool tryToLay(const QPoint &pos);
};

#endif // FIGURE_H
