#include "towericon.h"

#include "game.h"

extern Game *game;

BuildTowerIcon::BuildTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/tower.png"));
}

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (!game->building){
        game->building = new Tower();
        game->setCursor(QString(":/tower.png"));
    }
}

//---------------------------------tower1-------------------------


BuildTower1Icon::BuildTower1Icon(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/tower.png"));
}

void BuildTower1Icon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building){
        game->building = new Tower1();
        game->setCursor(QString(":/tower.png"));
    }
}

//---------------------------------tower2-------------------------

BuildTower2Icon::BuildTower2Icon(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/nuts.png"));
}

void BuildTower2Icon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building){
        game->building = new Tower2();
        game->setCursor(QString(":/nuts.png"));
    }
}

//---------------------------------tower3-------------------------

BuildTower3Icon::BuildTower3Icon(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/tower2.png"));
}

void BuildTower3Icon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building){
        game->building = new Tower3();
        game->setCursor(QString(":/tower2.png"));
    }
}
