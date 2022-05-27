#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> // list << element
#include <QPointF>

#include "map.h"

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Map *map;
    int armor;
    int direction;
    int position;
    int distance;

    Enemy(Map *map);
    void change_dir(int pos);
    bool block();
public slots:
    void move();
};

//--------------------------enemy1------------------------------

class Enemy1: public Enemy{
    Q_OBJECT
public:
    static int type;
    int damage;

    Enemy1(Map *map);
    bool attack();
public slots:
    void move();
};

//--------------------------enemy2------------------------------

class Enemy2: public Enemy{
    Q_OBJECT
public:
    static int type;
    //int damage;

    Enemy2(Map *map);
    //bool attack();
public slots:
    void move();
};
#endif // ENEMY_H
