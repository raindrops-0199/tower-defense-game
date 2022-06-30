#include <iostream>
#include <fstream>
#include "mainwindow.h"
#include "game.h"
#include "map.h"
using namespace std;

#include <QApplication>

Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Map *map = new Map(QString(":/map.txt"));
    //Map *map = new Map();

    game = new Game(map);
    game->show();
    return a.exec();
}
