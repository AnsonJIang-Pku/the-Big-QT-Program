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

Bomb::Bomb(int x, int y, int _Power, Player* _p, Game* game, QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent)
{
    this->game = game;
    int bombSize = 40;
    Power = _Power;
    player = _p;
    active = true;
    setPixmap(QPixmap(":/pictures/bombermanPic/bomb1_stand_0_0.png"));
    setPos(x - x % 40, y - y % 40);
    xBomb = x - x % 40;
    yBomb = y - y % 40;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(destroyItem()));
    timer->start(3000);
    bombsound = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    bombsound->setAudioOutput(audioOutput);
    bombsound->setSource(QUrl("qrc:/sounds/sound_effects/boom.wav"));
}
void Bomb::destroy() {
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(destroyItem()));
    timer->start(0);
}
void Bomb::setFlame(int x, int y) {
    Flame* flame = new Flame(x, y, this->game);
    this->game->scene->addItem(flame);
    audioOutput->setVolume(1);
    bombsound->play();
}
void Bomb :: destroyItem() {
    if (!active) {
        return;
    }
    int blockSize = 40;
    int bombSize = 40;
    int x0 = 40;
    int y0 = 160;
    int w = 520;
    int h = 320;
    QPointer<Map> map = this->game->map;
    QPointer<Player> player = this->player;

    int playerSize = player->playerSize;
    QPointer<QGraphicsScene> scene = game->scene;
//for set flame

    setFlame(xBomb, yBomb);
    for (int i = 1; i <= Power; i++) {
        if ((xBomb - x0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->type == EMPTY) {
            setFlame(xBomb - i * blockSize, yBomb);
            if (map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->bomb)
                map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->bomb->destroy();
        }
        if ((yBomb - y0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == EMPTY) {
            setFlame(xBomb, yBomb - i * blockSize);
            if (map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb)
                map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb->destroy();
        }
        if ((xBomb - x0 + i * blockSize) / blockSize <= 12 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->type == EMPTY) {
            setFlame(xBomb + i * blockSize, yBomb);
            if (map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->bomb)
                map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->bomb->destroy();
        }
        if ((yBomb - y0 + i * blockSize) / blockSize <= 7 && map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == EMPTY) {
            setFlame(xBomb, yBomb + i * blockSize);
            if (map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb)
                map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb->destroy();
        }

    }

//for destroy block
    bool a[4] = {0};
    for (int i = 1; i <= Power; i++) {
        if (!a[0] && (xBomb - x0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->removeItem();
            map->setEmptyCell((yBomb - y0) / blockSize, (xBomb - x0 - i * blockSize) / blockSize);
            setFlame(xBomb - i * blockSize, yBomb);
            a[0] = true;
        }
        if (!a[1] && (yBomb - y0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->removeItem();
            map->setEmptyCell((yBomb - y0 - i * blockSize) / blockSize, (xBomb - x0) / blockSize);
            setFlame(xBomb, yBomb - i * blockSize);
            a[1] = true;
        }
        if (!a[2] && (xBomb - x0 + i * blockSize) / blockSize <= 12 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->removeItem();
            map->setEmptyCell((yBomb - y0) / blockSize, (xBomb - x0 + i * blockSize) / blockSize);
            setFlame(xBomb + i * blockSize, yBomb);
            a[2] = true;
        }
        if (!a[3] && (yBomb - y0 + i * blockSize) / blockSize <= 7 && map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->removeItem();
            map->setEmptyCell((yBomb - y0 + i * blockSize) / blockSize, (xBomb - x0) / blockSize);
            setFlame(xBomb, yBomb + i * blockSize);
            a[3] = true;
        }
    }
    active = false;
    scene->removeItem(this);
    this->game->map->table[(yBomb - y0)/ blockSize][(xBomb - x0) / blockSize]->bomb = NULL;
    this->player->UsedBomb--;
    delete timer;
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
