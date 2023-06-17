#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Flame.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPointer>
#include <QList>
#include <QGraphicsItem>
#include <stdbool.h>


Flame::Flame(int x, int y, Game* game, QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent)
{
    this->game = game;
    setPixmap(QPixmap(":/pictures/bombermanPic/flame1_stand_0_0.png"));
    setPos(x, y);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Vanish()));
    timer->start(500);
}
void Flame::Vanish() {
    QPointer<QGraphicsScene> scene = game->scene;
    scene->removeItem(this);
    delete timer;
    return;
}
