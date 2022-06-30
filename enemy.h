#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> // list << element
#include <QPointF>
#include <QPropertyAnimation>
#include <QGraphicsPolygonItem>

#include "map.h"
#include "tower.h"

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Map *map;
    int armor;
    int direction;
    int position;
    int distance;
    //设置一个透明度的属性和属性动画，用于在受到攻击时改变透明度来展示受击效果
    Q_PROPERTY(float opac READ opacity WRITE setOpacity);
    QPropertyAnimation *anim;

    Enemy(Map *map);
    void change_dir(int pos);
    bool block();
    double distanceTo(QGraphicsItem * item);

public slots:
    void move();

protected:
    QGraphicsPolygonItem * attack_area;
    QPointF attack_dest;
    bool has_target;
};

//--------------------------enemy1------------------------------
//地面单位

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
//飞行单位，不会受到阻拦

class Enemy2: public Enemy{
    Q_OBJECT
public:
    static int type;
    //int damage;

    Enemy2(Map *map);
    void fire();
public slots:
    void move();
    void acquire_target();

};
#endif // ENEMY_H
