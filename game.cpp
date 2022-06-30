#include "game.h"
#include "enemy.h"
#include "map.h"
#include "towericon.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPen>
#include <QGraphicsLineItem>
#include <QObject>
#include <vector>
#include <QTimer>
#include <random>
#include <QDebug>
using namespace std;

#define ENEMY_TYPE_NUM 2

Game::Game(Map *map):map(map)
{
    // creat a scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // create the player
//    QGraphicsRectItem *player = new QGraphicsRectItem();
//    player->setRect(0,0,100,100); // change the rect from 0x0 (default) to 100x100 pixels
//    player->setPos(400,500); // TODO generalize to always be in the middle bottom of screen
//    // make the player focusable and set it to be the current focus
//    player->setFlag(QGraphicsItem::ItemIsFocusable);
//    player->setFocus();
//    // add the player to the scene
//    scene->addItem(player);

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){            
            QGraphicsRectItem *grid = new QGraphicsRectItem();
            grid->setRect(0, 0, 50, 50);
            grid->setPos(100 + 50 * j, 50 + 50 * i);
            scene->addItem(grid);
            int type = map->map[i][j];
            if (type == 0){
                grid->setBrush(Qt::darkCyan);
            }
            if (type == 1){
                grid->setBrush(Qt::cyan);
            }
            if (type == 2){
                grid->setBrush(Qt::gray);
            }
        }
    }

    // set curosr
    cursor = nullptr;
    building = nullptr;
    setMouseTracking(true);

    BuildTower1Icon * ic1 = new BuildTower1Icon();
    BuildTower2Icon * ic2 = new BuildTower2Icon();
    BuildTower3Icon * ic3 = new BuildTower3Icon();
    BuildTower4Icon * ic4 = new BuildTower4Icon();
    BuildTower5Icon * ic5 = new BuildTower5Icon();


    ic1->setPos(x(), y() + 10);
    ic2->setPos(x(), y() + 60);
    ic3->setPos(x(), y() + 110);
    ic4->setPos(x(), y() + 160);
    ic5->setPos(x(), y() + 210);

    scene->addItem(ic1);
    scene->addItem(ic2);
    scene->addItem(ic3);
    scene->addItem(ic4);
    scene->addItem(ic5);

    //spawn enemies
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(spawn()));
    timer->start(5000);

}

void Game::spawn()
{
    // create an enemy ramdomly
    double probability = 0.6;

    double random = (double)rand() / RAND_MAX;

    if (random < probability ){
        Enemy1 *enemy = new Enemy1(map);
        scene->addItem(enemy);
    }
    else if (random >= probability){
        Enemy2 *enemy = new Enemy2(map);
        scene->addItem(enemy);
    }
}


void Game::setCursor(QString filename){
    // if there is already a cursor, remove it first
    if (cursor){
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event){
    if (cursor){
        cursor->setPos(event->pos());
    }
}

void Game::mousePressEvent(QMouseEvent *event){
    // if we are building
    if (building){
        // return if the cursor is colliding with a tower
        QList<QGraphicsItem *> items = cursor->collidingItems();
        for (size_t i = 0, n = items.size(); i < n; i++){
            if (dynamic_cast<Tower*>(items[i])){
                return;
            }
        }
        // check grid type, return if not avaliable
        int x, y;
        x = (event->y() - 50) / 50;
        y = (event->x() - 100) / 50;
        //qDebug() << x << " " << y;

        if (map->map[x][y] == 0 ||
            (map->map[x][y] == 1 && dynamic_cast<Tower1*>(building)) ||
            (map->map[x][y] == 1 && dynamic_cast<Tower5*>(building)) ||
            (map->map[x][y] == 2 && dynamic_cast<Tower2*>(building)) ||
            (map->map[x][y] == 2 && dynamic_cast<Tower3*>(building)) ||
            (map->map[x][y] == 2 && dynamic_cast<Tower4*>(building))){
            return;
        }

        // otherwise, build at the clicked location

        scene->addItem(building);
        building->setPos(100 + 50 * y, 50 + 50 * x + 10);


        scene->removeItem(cursor);
        cursor = nullptr;
        building = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }

}










