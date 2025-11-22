#ifndef TWIDGET_H
#define TWIDGET_H

#include <QWidget>

class QPushButton;
class QLabel;
class GameMap;

class TWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TWidget(QWidget *parent = nullptr);

private:
    QPushButton *m_btnStart;
    QPushButton *m_btnReset;
    QLabel *m_lblScore;
    QLabel *m_lblBestScore;

    GameMap *m_gameMap;

    bool m_statusGame;
    bool m_statusPause;

    unsigned long m_score;
    unsigned long m_bestScore;

private slots:
    void startGame();
    void resetGame();
    void onGameOver();
    void setScore(unsigned long score);

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // TWIDGET_H
