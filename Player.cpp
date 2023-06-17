#include <stdio.h>
#include <stdbool.h>
#include <QList>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QSharedPointer>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QtDebug>

#include "Player.h"
#include "constants.h"


Player::Player(int _idx, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    for (int i = 0; i < 4; i++) record[i] = false;
    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;
    idx = _idx;
    step = 3;
    Power = 2;
    movementTimer.setInterval(16);
    connect(&movementTimer, SIGNAL(timeout()), this, SLOT(updateCharacterPosition()));
    movementTimer.start();
    setPixmap(QPixmap(":/pictures/bombermanPic/body1.png"));
}

void Player :: setGame(Game* game)
{
    this->game = game;
}

void Player :: keyPressEvent(QKeyEvent *event)
{
    xPlayer = x();
    yPlayer = y();
    if (idx == 0) {
        if (event->key() == Qt::Key_Left) {
            moveLeft = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveRight = false;
            moveUp = false;
            moveDown = false;
        }
        else if (event->key() == Qt::Key_Right) {
            moveRight = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveLeft = false;
            moveUp = false;
            moveDown = false;
        }
        else if (event->key() == Qt::Key_Up) {
            moveUp = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveLeft = false;
            moveRight = false;
            moveDown = false;
        }
        else if (event->key() == Qt::Key_Down) {
            moveDown = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveLeft = false;
            moveRight = false;
            moveUp = false;
        }
        else if (event->key() == Qt::Key_Enter) {
            int blockSize = 40;
            int playerSize = 40;
            int x0 = 40;
            int y0 = 160;
            int bomb_x = xPlayer + 23;
            int bomb_y = yPlayer + 55;
            Map* map = this->game->map;
            if (!map->table[(bomb_y - bomb_y % 40 - y0) / blockSize][(bomb_x - bomb_x % 40 - x0) / blockSize]->bomb) {
                map->table[(bomb_y - bomb_y % 40 - y0) / blockSize][(bomb_x - bomb_x % 40 - x0) / blockSize]->bomb = setBomb(bomb_x, bomb_y);
            }
        }
    }
    if (idx == 1) {
        if (event->key() == Qt::Key_A) {
            moveLeft = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveRight = false;
            moveUp = false;
            moveDown = false;
        }
        else if (event->key() == Qt::Key_D) {
            moveRight = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveLeft = false;
            moveUp = false;
            moveDown = false;
        }
        else if (event->key() == Qt::Key_W) {
            moveUp = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveLeft = false;
            moveRight = false;
            moveDown = false;
        }
        else if (event->key() == Qt::Key_S) {
            moveDown = true;
            record[0] = moveLeft;
            record[1] = moveRight;
            record[2] = moveUp;
            record[3] = moveDown;
            moveLeft = false;
            moveRight = false;
            moveUp = false;
        }
        else if (event->key() == Qt::Key_Space) {
            int blockSize = 40;
            int playerSize = 40;
            int x0 = 40;
            int y0 = 160;
            int bomb_x = xPlayer + 23;
            int bomb_y = yPlayer + 55;
            Map* map = this->game->map;
            if (!map->table[(bomb_y - bomb_y % 40 - y0) / blockSize][(bomb_x - bomb_x % 40 - x0) / blockSize]->bomb) {
                map->table[(bomb_y - bomb_y % 40 - y0) / blockSize][(bomb_x - bomb_x % 40 - x0) / blockSize]->bomb = setBomb(bomb_x, bomb_y);
            }
        }
    }

}
Bomb* Player :: setBomb(int xBomb, int yBomb) {
    Bomb* bomb = new Bomb(xBomb, yBomb, Power, this, this->game);
    this->game->scene->addItem(bomb);
    return bomb;
}
void Player :: keyReleaseEvent(QKeyEvent *event)
{
    if (idx == 0) {
        if (event->key() == Qt::Key_Left) {
            moveLeft = false;
            record[0] = false;
            moveRight = record[1];
            moveUp = record[2];
            moveDown = record[3];
        }
        else if (event->key() == Qt::Key_Right) {
            moveRight = false;
            record[1] = false;
            moveLeft = record[0];
            moveUp = record[2];
            moveDown = record[3];
        }
        else if (event->key() == Qt::Key_Up) {
            moveUp = false;
            record[2] = false;
            moveLeft = record[0];
            moveRight = record[1];
            moveDown = record[3];
        }
        else if (event->key() == Qt::Key_Down) {
            moveDown = false;
            record[3] = false;
            moveLeft = record[0];
            moveRight = record[1];
            moveUp = record[2];
        }
    }
    if (idx == 1) {
        if (event->key() == Qt::Key_A) {
            moveLeft = false;
            record[0] = false;
            moveRight = record[1];
            moveUp = record[2];
            moveDown = record[3];
        }
        else if (event->key() == Qt::Key_D) {
            moveRight = false;
            record[1] = false;
            moveLeft = record[0];
            moveUp = record[2];
            moveDown = record[3];
        }
        else if (event->key() == Qt::Key_W) {
            moveUp = false;
            record[2] = false;
            moveLeft = record[0];
            moveRight = record[1];
            moveDown = record[3];
        }
        else if (event->key() == Qt::Key_S) {
            moveDown = false;
            record[3] = false;
            moveLeft = record[0];
            moveRight = record[1];
            moveUp = record[2];
        }
    }
}

void  Player :: updateCharacterPosition()
{
    int dx = 0;
    int dy = 0;
    xPlayer = x();
    yPlayer = y();
    int blockSize = 40;
    int playerSize = 40;
    int x0 = 40;
    int y0 = 160;
    int w = 520;
    int h = 320;
    int box_x1 = xPlayer - x0;
    int box_y1 = yPlayer - y0 + 25;
    int box_x2 = box_x1 + 35;
    int box_y2 = box_y1 + 35;

    Map* map = this->game->map;
    if (moveLeft)
        if (box_x1 - step >= 0 && map->table[box_y1 / blockSize][(box_x1 - step) / blockSize]->type == EMPTY
            && map->table[box_y2 / blockSize][(box_x1 - step) / blockSize]->type == EMPTY)
            dx -= step;
    if (moveRight)
        if (box_x2 + step < w && map->table[box_y1 / blockSize][(box_x2 + step) / blockSize]->type == EMPTY
            && map->table[box_y2 / blockSize][(box_x2 + step) / blockSize]->type == EMPTY)
            dx += step;
    if (moveUp)
        if (box_y1 - step >= 0 && map->table[(box_y1 - step) / blockSize][box_x1 / blockSize]->type == EMPTY
            && map->table[(box_y1 - step) / blockSize][box_x2 / blockSize]->type == EMPTY)
            dy -= step;
    if (moveDown)
        if (box_y2 + step < h && map->table[(box_y2 + step) / blockSize][box_x1 / blockSize]->type == EMPTY
            && map->table[(box_y2 + step) / blockSize][box_x2 / blockSize]->type == EMPTY)
            dy += step;

//    if (moveLeft)
//        if(xPlayer + 20 - step >= x0 &&
//            (map->table[(yPlayer - y0 + playerSize) / blockSize][(xPlayer - x0 - step) / blockSize]->type) == EMPTY
//            && (map->table[(yPlayer - y0) / blockSize][(xPlayer - x0 - step) / blockSize]->type) == EMPTY)
//        dx -= step;
//    if (moveRight)
//        if(xPlayer + playerSize + step <= x0 + w &&
//            (map->table[(yPlayer - y0 + playerSize) / blockSize][(xPlayer - x0 + step + playerSize) / blockSize]->type) == EMPTY
//              &&(map->table[(yPlayer - y0) / blockSize][(xPlayer -x0 + step + playerSize) / blockSize])->type == EMPTY)
//        dx += step;
//    if (moveUp && dx == 0)
//        if(yPlayer + 30 - step >= y0 &&
//            (map->table[(yPlayer + 30 - y0 - step) / blockSize][(xPlayer - x0 + playerSize) / blockSize]->type) == EMPTY
//            &&(map->table[(yPlayer + 30 - y0 - step) / blockSize][(xPlayer - x0) / blockSize]->type) == EMPTY)

//        dy -= step;
//    if (moveDown && dx == 0)
//        if(yPlayer + 20 + playerSize + step <= y0 + h &&
//            (map->table[(yPlayer - y0 + step + playerSize) / blockSize][(xPlayer - x0 + playerSize) / blockSize]->type == EMPTY)
//            && (map->table[(yPlayer - y0 + step + playerSize) / blockSize][(xPlayer - x0) / blockSize])->type == EMPTY)
//        dy += step;

    // Update character position
    xPlayer += dx;
    yPlayer += dy;

    // Move the character
    setPos(xPlayer,yPlayer);
}




//void Player :: keyPressEvent(QKeyEvent *event)
//{
//    xPlayer = x();
//    yPlayer = y();
//    int blockSize = 100;
//    int playerSize = 40;
//    int step = 10;
//    int x0 = 40;
//    int y0 = 160;
//    int w = 520;
//    int h = 320;

//    Map* map = this->game->map;

//    if (event->key() == Qt::Key_A)
//    {
//        if(xPlayer + 20 - step >= x0 &&
//           (map->table[(yPlayer + playerSize) / blockSize][(xPlayer - step) / blockSize]->type) == EMPTY
//           && (map->table[(yPlayer) / blockSize][(xPlayer - step) / blockSize]->type) == EMPTY)
//        {
//            setPos(xPlayer-step,yPlayer);
//        }
//    }
//    else if (event->key() == Qt::Key_D)
//    {

//        if(xPlayer + playerSize + step <= x0 + w &&
//           (((map->table[(yPlayer + playerSize) / blockSize][(xPlayer + step + playerSize) / blockSize]->type) == EMPTY
//           &&(map->table[(yPlayer) / blockSize][(xPlayer + step + playerSize) / blockSize])->type == EMPTY)  ||
//             ((map->table[(yPlayer + playerSize) / blockSize][(xPlayer + step+ playerSize) / blockSize]->type) == EXIT
//            && (map->table[(yPlayer) / blockSize][(xPlayer+ step + playerSize) / blockSize])->type == EXIT)))
//        {
//            setPos(xPlayer+step,yPlayer);
//        }


//    }
//    else if (event->key() == Qt::Key_W)
//    {
//        if(yPlayer + 40 - step >= y0 &&
//           (map->table[(yPlayer - step) / blockSize][(xPlayer + playerSize) / blockSize]->type) == EMPTY
//           &&(map->table[(yPlayer - step) / blockSize][(xPlayer) / blockSize]->type) == EMPTY)
//        {
//            setPos(xPlayer,yPlayer-step);
//        }
//    }
//    else if (event->key() == Qt::Key_S)
//    {

//        if(yPlayer + 20 + playerSize + step <= y0 + h &&
//           (map->table[(yPlayer + step + playerSize) / blockSize][(xPlayer + playerSize) / blockSize]->type == EMPTY)
//           && (map->table[(yPlayer + step + playerSize) / blockSize][(xPlayer) / blockSize])->type == EMPTY)
//        {
//            setPos(xPlayer,yPlayer+step);
//           /* if((map->table[(yPlayer + playerSize) / blockSize][(xPlayer + playerSize) / blockSize]->type == EMPTY)
//               && (map->table[(yPlayer + playerSize) / blockSize][(xPlayer) / blockSize])->type == EMPTY)
//            {
//                game->goToTheNextLevel();
//            }*/
//        }
//    }
//    else if(event->key() == Qt::Key_Space)
//    {
//        this->game->setBomb(xPlayer + 23, yPlayer + 55);
//    }

//}

//сделать по границам клетки пермещение и коллизию так же
