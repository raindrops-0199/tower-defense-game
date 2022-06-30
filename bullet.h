#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

//-----------------default bullet---------------------
//塔发射的子弹

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=0);
public slots:
    void move();
    double getMaxRange();
    double getDistanceTravelled();
    void setMaxRange(double rng);
    void setDistanceTravelled(double dist);
protected:
    double maxRange;
    double distanceTravelled;
};

//----------------one attact bullet-----------------------
//敌方的子弹

class Bullet2: public Bullet{
    Q_OBJECT
public:
    Bullet2(QGraphicsItem * parent=0);
public slots:
    void move();
};

#endif // BULLET_H
