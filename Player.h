#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QList>
#include <QPointer>
#include <stdbool.h>
#include "Game.h"

class Player : public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    int xPlayer;
    int yPlayer;
    int Power;
    int playerSize;
    QPointer<Game> game;
    QTimer movementTimer;
    bool record[4];
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    int step;
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void setGame(Game* game);
private slots:
    void updateCharacterPosition();
    //void spawnEnemy();
    void setBomb(int xBomb, int yBomb);
};

#endif
