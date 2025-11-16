#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class CMap;
class Figure;
class RandBlock;

class GameMap : public QWidget
{
    Q_OBJECT
public:
    explicit GameMap(QWidget *parent = nullptr);
    ~GameMap();

signals:
    void gameOver();
    void scoreUp(unsigned long score);
    void levelUp(int level);

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

public:
    void moveLeft();
    void moveRight();
    void drop();
    void rotate();

public slots:
    void onStart();
    void onStop();
    void onReset();

private:
    int m_width;
    int m_height;
    int m_cellSize;
    int m_timeout;
    unsigned long m_score;
    int m_level;
    bool m_gameOver;
    CMap *m_map;
    QTimer m_timer;
    QPainter m_painter;
    QPixmap *m_pixmap;
    Figure *m_figure;

    RandBlock *m_random;

    void createFigure();

private slots:
    void updateMap();
    void onGameOver();
};

#endif // GAMEMAP_H
