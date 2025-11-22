#include "TWidget.h"
#include "GameMap.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>

TWidget::TWidget(QWidget *parent)
    : QWidget{parent}, m_statusGame{true}, m_statusPause{true}, m_bestScore{0ul}
{
    auto *topLayout = new QHBoxLayout;
    setLayout(topLayout);
    // left pane
    auto *cmdLayout = new QVBoxLayout;
    topLayout->addLayout(cmdLayout);
    m_btnStart = new QPushButton(tr("Start"));
    m_btnReset = new QPushButton(tr("Reset"));
    cmdLayout->addWidget(m_btnStart);
    cmdLayout->addWidget(m_btnReset);
    cmdLayout->addStretch(1);
    // middle
    m_gameMap = new GameMap;
    topLayout->addWidget(m_gameMap);
    // right pane
    auto *statLayout = new QVBoxLayout;
    topLayout->addLayout(statLayout);
    statLayout->addWidget(new QLabel(tr("Score")));
    m_lblScore = new QLabel;
    m_lblScore->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_lblScore->setAlignment(Qt::AlignCenter);
    statLayout->addWidget(m_lblScore);
    statLayout->addWidget(new QLabel(tr("Best score")));
    m_lblBestScore = new QLabel;
    m_lblBestScore->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_lblBestScore->setAlignment(Qt::AlignCenter);
    statLayout->addWidget(m_lblBestScore);
    statLayout->addStretch(1);

    connect(m_btnStart, &QPushButton::clicked, this, &TWidget::startGame);
    connect(m_btnReset, &QPushButton::clicked, this, &TWidget::resetGame);
    connect(m_gameMap, &GameMap::scoreUp, this, &TWidget::setScore);
    connect(m_gameMap, &GameMap::gameOver, this, &TWidget::onGameOver);

    m_btnStart->setFocusPolicy(Qt::NoFocus);
    m_btnReset->setFocusPolicy(Qt::NoFocus);
}

void TWidget::startGame()
{
    if (!m_statusGame)
        return;
    if (m_statusPause) {
        m_statusPause = false;
        m_btnStart->setText(tr("Pause"));
        m_gameMap->onStart();
    } else {
        m_statusPause = true;
        m_btnStart->setText(tr("Start"));
        m_gameMap->onStop();
    }
}

void TWidget::resetGame()
{
    m_statusGame = true;
    m_statusPause = false;
    m_btnStart->setText(tr("Pause"));
    m_btnStart->setDisabled(false);
    m_gameMap->onReset();
    m_gameMap->onStart();
}

void TWidget::onGameOver()
{
    m_statusGame = false;
    m_btnStart->setDisabled(true);
}

void TWidget::setScore(unsigned long score)
{
    m_score = score;
    if (m_score > m_bestScore) {
        m_bestScore = m_score;
        m_lblBestScore->setText(QString::number(m_bestScore));
    }
    m_lblScore->setText(QString::number(score));
}

void TWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        m_gameMap->moveLeft();
        break;
    case Qt::Key_Right:
        m_gameMap->moveRight();
        break;
    case Qt::Key_Up:
        m_gameMap->rotate();
        break;
    case Qt::Key_Down:
        m_gameMap->drop();
        break;
    case Qt::Key_Space:
        startGame();
        break;
    case Qt::Key_Escape:
        resetGame();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}
