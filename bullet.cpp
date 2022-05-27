#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <qmath.h>
#include <QPixmap>
#include <QDebug>

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent){
    // set graphics
    setPixmap(QPixmap(":/bullet.png"));

    // connect a timer to move()
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(50);

    // initialize values
    maxRange = 100;
    distanceTravelled = 0;
}

void Bullet::move(){
    int STEP_SIZE = 30;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    //-----------------------------------------------------------------

    QList<QGraphicsItem *> colliding_items = collidingItems();


    for (size_t i = 0, n = colliding_items.size(); i < n; ++i){

        // make sure it is an enemy
        Enemy * enemy = dynamic_cast<Enemy *>(colliding_items[i]);

        // see if distance is closer
        if (enemy){
            enemy->armor -= 1;
            //qDebug() << "armor -1";
            if (enemy->armor == 0){
                game->scene->removeItem(enemy);
                delete enemy;
            }
        }
    }
}

double Bullet::getMaxRange(){
    return maxRange;
}

double Bullet::getDistanceTravelled(){
    return distanceTravelled;
}

void Bullet::setMaxRange(double rng){
    maxRange = rng;
}

void Bullet::setDistanceTravelled(double dist){
    distanceTravelled = dist;
}

