#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include <QPropertyAnimation>

class Tower:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int armor;
    Q_PROPERTY(float opac READ opacity WRITE setOpacity);
    QPropertyAnimation *anim;

    Tower(QGraphicsItem * parent=0);
    double distanceTo(QGraphicsItem * item);
    virtual void fire();
public slots:
    void acquire_target();
protected:

    QGraphicsPolygonItem * attack_area;
    QPointF attack_dest;
    bool has_target;
};

//----------------------------------tower1---------------------------
//我方远程单位,可攻击范围内所有敌人

class Tower1:public Tower{
    Q_OBJECT
public:

    Tower1(QGraphicsItem * parent=0);
    void fire();
public slots:
    void acquire_target();
};

//----------------------------------tower2-------------------------------
//我方地面阻拦单位，仅阻拦敌方地面单位，且不攻击

class Tower2:public Tower{
    Q_OBJECT
public:

    Tower2(QGraphicsItem * parent=0);
};


//----------------------------------tower3-------------------------------
//我方近战单位，仅攻击敌方地面单位，有阻拦效果


class Tower3:public Tower{
    Q_OBJECT
public:
    int damage;

    Tower3(QGraphicsItem * parent=0);
    void fire();
public slots:
    void acquire_target();
};

//----------------------------------tower4-------------------------------
//我方近战单位，有阻拦效果，可攻击敌方地面与飞行单位


class Tower4:public Tower{
    Q_OBJECT
public:
    int damage;

    Tower4(QGraphicsItem * parent=0);
    void fire();
public slots:
    void acquire_target();
};


//----------------------------------tower5-------------------------------
//我方远程单位，但只攻击敌方地面单位

class Tower5:public Tower{
    Q_OBJECT
public:
    int damage;

    Tower5(QGraphicsItem * parent=0);
    void fire();
public slots:
    void acquire_target();
};


#endif // TOWER_H
