#ifndef TOWERICON_H
#define TOWERICON_H


#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildTowerIcon: public QGraphicsPixmapItem{
public:
    BuildTowerIcon(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

//-------------------------tower1--------------------------

class BuildTower1Icon: public BuildTowerIcon{
public:
    BuildTower1Icon(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

//-------------------------tower2------------------------------

class BuildTower2Icon: public BuildTowerIcon{
public:
    BuildTower2Icon(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


//-------------------------tower3------------------------------

class BuildTower3Icon: public BuildTowerIcon{
public:
    BuildTower3Icon(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

//-------------------------tower4------------------------------

class BuildTower4Icon: public BuildTowerIcon{
public:
    BuildTower4Icon(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


//-------------------------tower5------------------------------

class BuildTower5Icon: public BuildTowerIcon{
public:
    BuildTower5Icon(QGraphicsItem * parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


#endif // TOWERICON_H
