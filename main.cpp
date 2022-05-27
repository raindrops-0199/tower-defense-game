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

//    ofstream out("D:/OneDrive/undergraduate/curriculum/advanced-programming/project2/code/TowerDefense/resource/map.txt");
//    if (!out){
//        cout << "wrong";
//    }
//    for (int i = 0; i < 10; i++){
//        for (int j = 0; j < 10; j++){
//            out << i << ',' << j << ',' << map->map[i][j] << ';';
//        }
//    }

    game = new Game(map);
    game->show();
    return a.exec();
}
