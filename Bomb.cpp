#include "Bomb.h"
#include "Player.h"
#include "Map.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QPointer>
#include <QList>
#include <QGraphicsItem>
#include <stdbool.h>

bool isEnemyLeftRightExist = true;
bool isEnemyUpDownExist = true;

Bomb::Bomb(int x, int y, Game* game, QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent)
{
    this->game = game;
    int bombSize = 40;
    setPixmap(QPixmap(":/pictures/bombermanPic/bomb1_stand_0_0.png"));
    setPos(x - x % 40, y - y % 40);
    xBomb = x - x % 40;
    yBomb = y - y % 40;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(destroyItem()));
    timer->start(3000);


}

void Bomb :: destroyItem() {
    int blockSize = 40;
    int bombSize = 40;
    int x0 = 40;
    int y0 = 160;
    int w = 520;
    int h = 320;
    QPointer<Map> map = this->game->map;
    QPointer<Player> player = this->game->player;

    int playerSize = player->playerSize;
    QPointer<QGraphicsScene> scene = game->scene;
//for destroy block
//    if ((yBomb - bombSize) > y0 && ((map->table[(yBomb - bombSize) / blockSize][(xBomb + bombSize) / blockSize])->type == DESTRUCTIBLE_BLOCK ||
//                                   ((map->table[(yBomb - bombSize) / blockSize][(xBomb) / blockSize])->type == DESTRUCTIBLE_BLOCK)))
//    {
//        map->table[(yBomb - bombSize) / blockSize][xBomb / blockSize]->removeItem(map->table[(yBomb - bombSize) / blockSize][xBomb / blockSize]);
//        map->setEmptyCell((yBomb - bombSize) / blockSize, xBomb / blockSize);
//    }

//    if(yBomb < y0 + h && ((map->table[(yBomb + 2* bombSize)/blockSize][(xBomb)/blockSize])->type == DESTRUCTIBLE_BLOCK ||
//                       ((map->table[(yBomb + 2*bombSize)/blockSize][(xBomb+bombSize)/blockSize])->type == DESTRUCTIBLE_BLOCK)))
//    {
//        map->table[(yBomb + 2*bombSize)/blockSize][(xBomb+bombSize)/blockSize]->removeItem(map->table[(yBomb + 2*bombSize)/blockSize][(xBomb+bombSize)/blockSize]);
//        map->setEmptyCell((yBomb + 2*bombSize)/blockSize, (xBomb+bombSize)/blockSize);
//    }
//    if ((xBomb - bombSize) > x0 && ((map->table[yBomb/blockSize][xBomb/blockSize])->type == DESTRUCTIBLE_BLOCK ||
//                                   (map->table[yBomb/blockSize][(xBomb - bombSize)/blockSize])->type == DESTRUCTIBLE_BLOCK))
//    {
//        map->table[yBomb/blockSize][(xBomb - bombSize)/blockSize]->removeItem(map->table[yBomb/blockSize][(xBomb - bombSize)/blockSize]);
//        map->setEmptyCell(yBomb/blockSize, (xBomb - bombSize)/blockSize);
//    }

//    if ((xBomb + bombSize) < x0 + w && ((map->table[yBomb/blockSize][(xBomb+bombSize)/blockSize])->type == DESTRUCTIBLE_BLOCK ||
//                                     (map->table[yBomb/blockSize][(xBomb + 2*bombSize)/blockSize])->type == DESTRUCTIBLE_BLOCK))
//    {
//        map->table[yBomb/blockSize][(xBomb + 2*bombSize)/blockSize]->removeItem(map->table[yBomb/blockSize][(xBomb + 2*bombSize)/blockSize]);
//        map->setEmptyCell(yBomb/blockSize, (xBomb + 2*bombSize)/blockSize);
//    }
////for destroy player

//    if ((yBomb - bombSize) > 0 && (map->table[(yBomb - bombSize) / blockSize][(xBomb + bombSize) / blockSize] == map->table[(player->yPlayer + playerSize)/blockSize][(player->xPlayer)/blockSize]) ||
//        (map->table[(yBomb - bombSize) / blockSize][(xBomb) / blockSize] == map->table[(player->yPlayer + playerSize)/blockSize][(player->xPlayer + playerSize)/blockSize]))
//    {
//        player->setPos(0, 0);
//        player->yPlayer = 0;
//        player->xPlayer = 0;
//        this->game->health->decrease();
//    }

//    if (yBomb < 500 &&
//    ((map->table[(yBomb + 2* bombSize)/blockSize][(xBomb)/blockSize] == map->table[(player->yPlayer)/blockSize][(player->xPlayer)/blockSize] ||
//    (map->table[(yBomb + 2*bombSize)/blockSize][(xBomb+bombSize)/blockSize]== map->table[(player->yPlayer)/blockSize][(player->xPlayer + playerSize)/blockSize]))))
//    {
//        player->setPos(0, 0);
//        player->yPlayer = 0;
//        player->xPlayer = 0;
//        this->game->health->decrease();
//    }

//    if((xBomb - bombSize) > 0 &&
//    (((map->table[yBomb/blockSize][xBomb/blockSize]) == map->table[(player->yPlayer)/blockSize][(player->xPlayer + playerSize)/blockSize] ||
//      (map->table[yBomb/blockSize][(xBomb - bombSize)/blockSize]) == map->table[(player->yPlayer + playerSize)/blockSize][(player->xPlayer + playerSize)/blockSize])))
//    {
//        player->setPos(0, 0);
//        player->yPlayer = 0;
//        player->xPlayer = 0;
//        this->game->health->decrease();
//    }

///*    ((map->table[yBomb/blockSize][(xBomb+bombSize)/blockSize])->type == DESTRUCTIBLE_BLOCK ||
//     (map->table[yBomb/blockSize][(xBomb + 2*bombSize)/blockSize])->type == DESTRUCTIBLE_BLOCK))*/

//    if ((xBomb + bombSize) < 700 &&
//    (((map->table[yBomb/blockSize][(xBomb+bombSize)/blockSize]) == map->table[(player->yPlayer)/blockSize][(player->xPlayer)/blockSize] ||
//    (map->table[yBomb/blockSize][(xBomb + 2*bombSize)/blockSize]) == map->table[(player->yPlayer)/blockSize][(player->xPlayer + playerSize)/blockSize])))
//    {
//        player->setPos(0, 0);
//        player->yPlayer = 0;
//        player->xPlayer = 0;
//        this->game->health->decrease();
//    }

    scene->removeItem(this);
    delete timer;
    return;
}

/*
(map->table[(player->yPlayer)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[yBomb/blockSize][xBomb/blockSize]) ||
(map->table[(player->yPlayer+ player->playerSize)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[(yBomb+bombSize)/blockSize][xBomb/blockSize])||
((map->table[(player->yPlayer + player->playerSize)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[yBomb/blockSize][(xBomb + bombSize)/blockSize] ||
(map->table[(player->yPlayer + player->playerSize)/blockSize][(player->xPlayer)/blockSize] ==
map->table[yBomb/blockSize][xBomb/blockSize]) ||
(map->table[(player->yPlayer)/blockSize][(player->xPlayer)/blockSize] ==
map->table[yBomb/blockSize][(xBomb + bombSize)/blockSize]) ||
(map->table[(player->yPlayer + player->playerSize)/blockSize][(player->xPlayer)/blockSize] ==
map->table[(yBomb + bombSize)/blockSize][(xBomb + bombSize)/blockSize]) ||
(map->table[(player->yPlayer)/blockSize][(player->xPlayer)/blockSize] ==
map->table[(yBomb + bombSize)/blockSize][(xBomb)/blockSize]) ||
(map->table[(player->yPlayer)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[(yBomb + bombSize)/blockSize][(xBomb + bombSize)/blockSize]))))*/
