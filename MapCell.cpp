#include <QGraphicsScene>

#include "MapCell.h"

MapCell::MapCell(CellType cellType)
{
    type = cellType;
}

void MapCell::removeItem(MapCell *item)
{
    scene()->removeItem(this);
}

MapCell::MapCell(){}
