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
    QPushButton *m_btnStop;
    QPushButton *m_btnReset;
    QLabel *m_lblScore;

    GameMap *m_gameMap;

private slots:
    void setScore(unsigned long score);
};

#endif // TWIDGET_H
