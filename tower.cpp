#include "tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "bullet.h"
#include <QPointF>
#include <QLineF>
#include "game.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include "enemy.h"

extern Game * game;

#define PICHEIGHT 50
#define PICWIDTH 50

#include <QDebug>
Tower::Tower(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent){

    setPixmap(QPixmap(":/tower.png"));

}

double Tower::distanceTo(QGraphicsItem *item){
    // returns the distance to the item
    QLineF ln(this->pos(),item->pos());
    return ln.length();
}

void Tower::fire(){
    Bullet * bullet = new Bullet();
    bullet->setPos(x()+44,y()+44);

    QLineF ln(QPointF(x()+44,y()+44),attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
    //qDebug() << "attack";
}

void Tower::acquire_target(){
    // get a list of all enemies that collide with attack_area, find the closest one
    // and set it's position as the attack_dest

    // get a list of all enemies within attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    // assume tower does not have a target, unless we find one
    has_target = false;

    // find the closest Enemy
    double closest_dist = 300;
    QPointF closest_pt(0,0);
    for (size_t i = 0, n = colliding_items.size(); i < n; ++i){

        // make sure it is an enemy
        Enemy * enemy = dynamic_cast<Enemy *>(colliding_items[i]);

        // see if distance is closer
        if (enemy){
            double this_dist = distanceTo(colliding_items[i]);
            if (this_dist < closest_dist){
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    // if has target, set the closest enemy as the attack_dest, and fire
    if (has_target){
        closest_pt += QPointF(PICWIDTH / 2, PICHEIGHT / 2);
        attack_dest = closest_pt;
        fire();
    }
}


//-----------------------------------------------------------tower1--------------------------------
//我方远程单位,可攻击范围内所有敌人


Tower1::Tower1(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/tower.png"));
    armor = 15;

    // create points vector
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
               << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // scale points
    int SCALE_FACTOR = 75;
    for (int i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));

    // move the polygon
    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+ PICWIDTH / 2,y()+PICHEIGHT / 2);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    // set attack_dest
    attack_dest = QPointF(0,0);
    has_target = false;

    // connect a timer to attack_target/aquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(1000);
}

void Tower1::fire()
{
    //TODO:: change
    Bullet * bullet = new Bullet();
    bullet->setPos(x() + PICWIDTH / 2,y() + PICHEIGHT / 2);

    QLineF ln(QPointF(x() + PICWIDTH / 2,y() + PICHEIGHT / 2),attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
    //qDebug() << "attack";

}

void Tower1::acquire_target()
{
    Tower::acquire_target();
}


//-------------------------------------------tower2----------------------------------
//我方地面阻拦单位，仅阻拦敌方地面单位，且不攻击


Tower2::Tower2(QGraphicsItem *parent)
{
    armor = 60;
    setPixmap(QPixmap(":/nuts.png"));
}


//-------------------------------------------tower3------------------------------------
//我方近战单位，仅攻击敌方地面单位，有阻拦效果


Tower3::Tower3(QGraphicsItem *parent):damage(1)
{
    setPixmap(QPixmap(":/tower2.png"));
    armor = 40;

    // create points vector
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
               << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // scale points
    int SCALE_FACTOR = 25;
    for (int i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));

    // move the polygon
    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);;
    QPointF tower_center(x()+ PICWIDTH / 2,y()+PICHEIGHT / 2);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());


    // set attack_dest
    attack_dest = QPointF(0,0);
    has_target = false;

    // connect a timer to attack_target/aquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(1000);
}

void Tower3::fire()
{
    //TODO:: change
    Bullet * bullet = new Bullet();
    bullet->setPos(x() + PICWIDTH / 2,y() + PICHEIGHT / 2);

    QLineF ln(QPointF(x() + PICWIDTH / 2,y() + PICHEIGHT / 2),attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
    //qDebug() << "attack";

}

void Tower3::acquire_target(){
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    // assume tower does not have a target, unless we find one
    has_target = false;

    // find the closest Enemy
    double closest_dist = 300;
    QPointF closest_pt(0,0);
    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        // make sure it is an enemy
        Enemy1 * enemy1 = dynamic_cast<Enemy1 *>(colliding_items[i]);

        // see if distance is closer
        if (enemy1){
            double this_dist = distanceTo(colliding_items[i]);
            if (this_dist < closest_dist){
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    // if has target, set the closest enemy as the attack_dest, and fire
    if (has_target){
        closest_pt += QPointF(PICWIDTH / 2, PICHEIGHT / 2);
        attack_dest = closest_pt;
        fire();
    }
}


//----------------------------------tower4-------------------------------
//我方近战单位，有阻拦效果，可攻击敌方地面与飞行单位


Tower4::Tower4(QGraphicsItem *parent):damage(2)
{
    setPixmap(QPixmap(":/tower4.png"));
    armor = 40;

    // create points vector
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
               << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // scale points
    int SCALE_FACTOR = 35;
    for (int i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));

    // move the polygon
    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);;
    QPointF tower_center(x()+ PICWIDTH / 2,y()+PICHEIGHT / 2);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());


    // set attack_dest
    attack_dest = QPointF(0,0);
    has_target = false;

    // connect a timer to attack_target/aquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(1000);
}

void Tower4::fire()
{
    Bullet * bullet = new Bullet();
    bullet->setPos(x() + PICWIDTH / 2,y() + PICHEIGHT / 2);

    QLineF ln(QPointF(x() + PICWIDTH / 2,y() + PICHEIGHT / 2),attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void Tower4::acquire_target()
{
    Tower::acquire_target();
}


//----------------------------------tower5-------------------------------
//我方远程单位，但只攻击敌方地面单位

Tower5::Tower5(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/tower5.png"));
    armor = 15;

    // create points vector
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
               << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // scale points
    int SCALE_FACTOR = 75;
    for (int i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));

    // move the polygon
    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);;
    QPointF tower_center(x()+ PICWIDTH / 2,y()+PICHEIGHT / 2);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());



    // set attack_dest
    attack_dest = QPointF(0,0);
    has_target = false;

    // connect a timer to attack_target/aquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(1000);
}

void Tower5::fire()
{
    Bullet * bullet = new Bullet();
    bullet->setPos(x() + PICWIDTH / 2,y() + PICHEIGHT / 2);

    QLineF ln(QPointF(x() + PICWIDTH / 2,y() + PICHEIGHT / 2),attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void Tower5::acquire_target()
{
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    // assume tower does not have a target, unless we find one
    has_target = false;

    // find the closest Enemy
    double closest_dist = 300;
    QPointF closest_pt(0,0);
    for (size_t i = 0, n = colliding_items.size(); i < n; ++i){

        // make sure it is an enemy
        Enemy1 * enemy1 = dynamic_cast<Enemy1 *>(colliding_items[i]);

        // see if distance is closer
        if (enemy1){
            double this_dist = distanceTo(colliding_items[i]);
            if (this_dist < closest_dist){
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    // if has target, set the closest enemy as the attack_dest, and fire
    if (has_target){
        closest_pt += QPointF(PICWIDTH / 2, PICHEIGHT / 2);
        attack_dest = closest_pt;
        fire();
    }
}
