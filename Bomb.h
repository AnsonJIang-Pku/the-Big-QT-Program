#ifndef BOMB_H
#define BOMB_H

#include <stdio.h>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointer>

#include "Map.h"

class Bomb: public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
private:
    int xBomb;
    int yBomb;
    QTimer* timer;
public slots:
    void destroyItem();
public:
    QPointer<Game> game;
    Bomb(int x, int y, Game* game, QGraphicsItem* parent = 0);
};

#endif
