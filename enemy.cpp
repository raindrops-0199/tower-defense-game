#include "enemy.h"
#include "map.h"
#include "tower.h"
#include "game.h"
#include "towericon.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QList>

extern Game * game;

Enemy::Enemy(Map *map):map(map), armor(10), position(0), distance(0)
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

//----------------------------------enemy1------------------------------------

Enemy1::Enemy1(Map *map): Enemy(map), damage(1){
    // set position
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

        // make sure it is an enemy
        Tower2* tower2 = dynamic_cast<Tower2 *>(colliding_items[i]);
        Tower3* tower3 = dynamic_cast<Tower3 *>(colliding_items[i]);
        // see if distance is closer
        if (tower2){
            tower2->armor -= 1;
            if (tower2->armor == 0){
                game->scene->removeItem(tower2);
                delete tower2;
            }
            return true;
        }
        else if (tower3){
            tower3->armor -= 1;
            if (tower3->armor == 0){
                game->scene->removeItem(tower3);
                delete tower3;
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

    if (distance == 50){
        distance = 0;
        position++;
        Enemy::change_dir(position);

    }
    if (position != map->path.size()){
        distance += 5;
        if (direction == 0){
            // left
            setPos(x() + 5, y());
        }
        else if (direction == 1){
            // up
            setPos(x(), y() - 5);
        }
        else if (direction == 2){
            // right
            setPos(x() - 5, y());
        }
        else if (direction == 3){
            // down
            setPos(x(), y() + 5);
        }
    }
    else{
        scene()->removeItem(this);
        delete this;
        return;
    }
}

//----------------------------------enemy2-----------------------------------
//飞行单位，不会收到阻拦

Enemy2::Enemy2(Map *map):Enemy(map)
{
    // set position
    setPos(120 + map->path[0].second * 50 - 20, 80 + map->path[0].first * 50 - 20);

    setPixmap(QPixmap(":/bird.png"));

    //qDebug() << "created";

    Enemy::change_dir(0);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Enemy2::move()
{
    if (distance == 50){
        distance = 0;
        position++;
        Enemy::change_dir(position);

    }
    if (position != map->path.size()){
        int dis = 5;
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


