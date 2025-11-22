#include "GameMap.h"
#include "CMap.h"
#include "Figure.h"
#include "RandBlock.h"

#include <QPixmap>
#include <QMargins>
#include <QKeyEvent>

GameMap::GameMap(QWidget *parent)
    : QWidget{parent}
    , m_width{10}, m_height{20}, m_cellSize{20}
{
    m_timeout = 500;
    m_figure = nullptr;
    m_map = new CMap(m_width, m_height);
    m_pixmap = new QPixmap(m_width*m_cellSize, m_height*m_cellSize);

    m_random = new RandBlock(Figure::ShapeI, Figure::ShapeZ);

    setFixedSize(m_pixmap->size());
    connect(&m_timer, &QTimer::timeout, this, QOverload<>::of(&GameMap::updateMap));
    connect(this, &GameMap::gameOver, this, &GameMap::onGameOver);
    QTimer::singleShot(100, this, &GameMap::onReset);
}

GameMap::~GameMap()
{
    delete m_map;
    delete m_pixmap;
    delete m_random;
    delete m_figure;
}

void GameMap::paintEvent(QPaintEvent *event)
{
    m_painter.begin(m_pixmap);
    m_painter.fillRect(m_pixmap->rect(), Qt::black);
    QRect box(0, 0, m_cellSize, m_cellSize);
    box -= QMargins(1, 1, 1, 1);
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            box.moveTo(x*m_cellSize + 1, y*m_cellSize + 1);
            m_painter.fillRect(box, m_map->color(x, y));
        }
    }
    if (m_gameOver) {
        m_painter.fillRect(m_pixmap->rect(), QColor(90, 90, 90, 190));
        m_painter.setFont(QFont("Verdana", 16, 60));
        m_painter.setPen(Qt::white);
        m_painter.drawText(m_pixmap->rect(), Qt::AlignCenter, tr("Game Over!"));
    }
    if (m_gamePause) {
        m_painter.fillRect(m_pixmap->rect(), QColor(90, 90, 90, 190));
        m_painter.setFont(QFont("Verdana", 16, 60));
        m_painter.setPen(Qt::white);
        m_painter.drawText(m_pixmap->rect(), Qt::AlignCenter, tr("Pause"));
    }
    m_painter.end();
    m_painter.begin(this);
    m_painter.drawPixmap(0, 0, *m_pixmap);
    m_painter.end();
}

void GameMap::moveLeft()
{
    if (m_figure && m_timer.isActive()) {
        m_figure->moveL();
        update();
    }
}

void GameMap::moveRight()
{
    if (m_figure && m_timer.isActive()) {
        m_figure->moveR();
        update();
    }
}

void GameMap::drop()
{
    if (m_figure && m_timer.isActive()) {
        m_figure->moveDown();
        update();
    }
}

void GameMap::rotate()
{
    if (m_figure && m_timer.isActive()) {
        m_figure->rotate();
        update();
    }
}

void GameMap::onStart()
{
    if (!m_gameOver) {
        m_gamePause = false;
        update();
        m_timer.start(m_timeout);
    }
}

void GameMap::onStop()
{
    m_gamePause = true;
    m_timer.stop();
    update();
}

void GameMap::onReset()
{
    m_timer.stop();
    if (m_figure) {
        delete m_figure;
        m_figure = nullptr;
    }
    m_pixmap->fill(Qt::black);
    m_map->reset();
    m_score = 0ul;
    m_level = 0;
    m_gameOver = false;
    m_gamePause = false;
    emit scoreUp(m_score);
    emit levelUp(m_level);
    update();
}

void GameMap::updateMap()
{
    if (m_map->eraseLines()) {
        update();
        return;
    }
    if (!m_figure) {    // spawn figure if is doesn't exist
        m_figure = new Figure(m_map, Figure::Shape(m_random->rand()));
        if (!m_figure->isValid()) {
            m_timer.stop();
            delete m_figure;
            m_figure = nullptr;
            emit gameOver();
            return;
        }
    } else if (!m_figure->moveDown()) { // else try to move it
        delete m_figure;
        m_figure = nullptr;
        int dScore = m_map->searchFullLines();
        if (dScore > 0) {
            m_score += dScore;
            emit scoreUp(m_score);
        }
    }
    update();
}

void GameMap::onGameOver()
{
    m_gameOver = true;
    update();
}
