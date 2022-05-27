#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "map.h"
#include "tower.h"
using namespace std;

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene *scene;
    Map *map;
    QGraphicsPixmapItem * cursor;
    int enemiesSpawned;
    int maxNumberOfEnemies;
    QList<QPointF> pointsToFollow;
    Tower *building;

    Game(Map *map);
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void spawn();
};

#endif // GAME_H
