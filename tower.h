#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

class Tower:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int armor;

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

class Tower1:public Tower{
    Q_OBJECT
public:
    int armor;

    Tower1(QGraphicsItem * parent=0);
    void fire();
public slots:
    void acquire_target();
};

//----------------------------------tower2-------------------------------

class Tower2:public Tower{
    Q_OBJECT
public:
    int armor;

    Tower2(QGraphicsItem * parent=0);
};


//----------------------------------tower3-------------------------------

class Tower3:public Tower{
    Q_OBJECT
public:
    int armor;
    int damage;

    Tower3(QGraphicsItem * parent=0);
    void fire();
public slots:
    void acquire_target();
};


#endif // TOWER_H
