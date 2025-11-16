#include "TWidget.h"
#include "GameMap.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>

TWidget::TWidget(QWidget *parent)
    : QWidget{parent}
{
    auto *topLayout = new QHBoxLayout;
    setLayout(topLayout);
    // left pane
    auto *cmdLayout = new QVBoxLayout;
    topLayout->addLayout(cmdLayout);
    m_btnStart = new QPushButton(tr("Start"));
    m_btnStop  = new QPushButton(tr("Stop"));
    m_btnReset = new QPushButton(tr("Reset"));
    cmdLayout->addWidget(m_btnStart);
    cmdLayout->addWidget(m_btnStop);
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
    statLayout->addStretch(1);

    connect(m_btnStart, &QPushButton::clicked, m_gameMap, &GameMap::onStart);
    connect(m_btnStop,  &QPushButton::clicked, m_gameMap, &GameMap::onStop);
    connect(m_btnReset, &QPushButton::clicked, m_gameMap, &GameMap::onReset);
    connect(m_gameMap, &GameMap::scoreUp, this, &TWidget::setScore);

    installEventFilter(m_gameMap);
    setFocusPolicy(Qt::NoFocus);
    m_btnStart->setFocusPolicy(Qt::NoFocus);
    m_btnStop->setFocusPolicy(Qt::NoFocus);
    m_btnReset->setFocusPolicy(Qt::NoFocus);
}

void TWidget::setScore(unsigned long score)
{
    m_lblScore->setText(QString::number(score));
}
