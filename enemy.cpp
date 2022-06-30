#include "enemy.h"
#include "map.h"
#include "tower.h"
#include "game.h"
#include "towericon.h"
#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QList>
#include <QPainter>

extern Game * game;
#define PICHEIGHT 50
#define PICWIDTH 50

Enemy::Enemy(Map *map):map(map), position(0), distance(0)
{}

void Enemy::move()
{}

void Enemy::change_dir(int pos){
    if (map->path[pos + 1].second - map->path[pos].second == 1){
        direction = 0;
        return;
    }
    else if (map->path[pos + 1].first - map->path[pos].first == -1){
        direction = 1;
        return;
    }
    else if (map->path[pos + 1].second - map->path[pos].second == -1){
        direction = 2;
        return;
    }
    else if (map->path[pos + 1].first - map->path[pos].first == 1){
        direction = 3;
        return;
    }
}

double Enemy::distanceTo(QGraphicsItem *item)
{
    QLineF ln(this->pos(),item->pos());
    return ln.length();
}

//----------------------------------enemy1------------------------------------

Enemy1::Enemy1(Map *map): Enemy(map), damage(1){
    // set position
    armor = 10;
    setPos(125 + map->path[0].second * 50 - 20, 80 + map->path[0].first * 50 - 20);

    setPixmap(QPixmap(":/pig.png"));

    //qDebug() << "created";

    Enemy::change_dir(0);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

bool Enemy1::attack(){
    QList<QGraphicsItem *> colliding_items = collidingItems();


    for (size_t i = 0, n = colliding_items.size(); i < n; ++i){

        Tower* tower = dynamic_cast<Tower *>(colliding_items[i]);
        if (tower){
            tower->armor -= 1;

            tower->anim = new QPropertyAnimation(tower, "opac");
            tower->anim->setStartValue(0.5);
            tower->anim->setEndValue(1);
            tower->anim->setDuration(1000);
            tower->anim->setEasingCurve(QEasingCurve::OutQuint);
            tower->anim->start();

            if (tower->armor == 0){
                game->scene->removeItem(tower);
                delete tower;
            }
            return true;
        }
    }
    return false;
}

void Enemy1::move()
{
    if (attack()){
        return;
    }

    if (distance >= 50){
        distance = 0;
        position++;
        Enemy::change_dir(position);

    }
    if (position != map->path.size()){
        int dis = 4;
        distance += dis;
        if (direction == 0){
            // left
            setPos(x() + dis, y());
        }
        else if (direction == 1){
            // up
            setPos(x(), y() - dis);
        }
        else if (direction == 2){
            // right
            setPos(x() - dis, y());
        }
        else if (direction == 3){
            // down
            setPos(x(), y() + dis);
        }
    }
    else{
        scene()->removeItem(this);
        delete this;
        return;
    }
}

//----------------------------------enemy2-----------------------------------
//飞行单位，不会受到阻拦

Enemy2::Enemy2(Map *map):Enemy(map)
{
    armor = 10;
    // set position
    setPos(120 + map->path[0].second * 50 - 20, 80 + map->path[0].first * 50 - 20);

    setPixmap(QPixmap(":/bird.png"));

    //qDebug() << "created";

    Enemy::change_dir(0);

    QTimer *timer1 = new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(move()));
    timer1->start(50);


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
    qDebug() << poly_center;
    QPointF enemy_center(x()+ PICWIDTH / 2,y()+PICHEIGHT / 2);
    QLineF ln(poly_center,enemy_center);  
    attack_area->setPos(ln.dx(),ln.dy());
    qDebug() << attack_area->x();
    //qDebug() << ln;


    // set attack_dest
    attack_dest = QPointF(0,0);
    has_target = false;

    // connect a timer to attack_target/aquire_target
    QTimer * timer2 = new QTimer();
    connect(timer2,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer2->start(1000);
}

void Enemy2::fire()
{
    Bullet2 * bullet = new Bullet2();
    bullet->setPos(x()+44,y()+44);

    QLineF ln(QPointF(x()+44,y()+44),attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void Enemy2::move()
{
    if (distance >= 50){
        distance = 0;
        position++;
        Enemy::change_dir(position);

    }
    if (position != map->path.size()){
        int dis = 3;
        distance += dis;
        if (direction == 0){
            // left
            setPos(x() + dis, y());
        }
        else if (direction == 1){
            // up
            setPos(x(), y() - dis);
        }
        else if (direction == 2){
            // right
            setPos(x() - dis, y());
        }
        else if (direction == 3){
            // down
            setPos(x(), y() + dis);
        }
    }
    else{
        scene()->removeItem(this);
        delete this;
        return;
    }
}

void Enemy2::acquire_target()
{
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
        Tower * tower = dynamic_cast<Tower *>(colliding_items[i]);

        // see if distance is closer
        if (tower){
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


