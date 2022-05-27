#include "map.h"
#include <vector>
#include <QFile>
#include <QDebug>
using namespace std;

vector<string> split(const string &str, const string &pattern);

Map::Map(){
//    map = {
//        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
//        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
//        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
//        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//    };

    path.push_back(make_pair(8, 0));
    path.push_back(make_pair(8, 1));
    path.push_back(make_pair(8, 2));
    path.push_back(make_pair(8, 3));
    path.push_back(make_pair(8, 4));
    path.push_back(make_pair(7, 4));
    path.push_back(make_pair(6, 4));
    path.push_back(make_pair(5, 4));
    path.push_back(make_pair(4, 4));
    path.push_back(make_pair(4, 5));
    path.push_back(make_pair(4, 6));
    path.push_back(make_pair(4, 7));
    path.push_back(make_pair(3, 7));
    path.push_back(make_pair(2, 7));
    path.push_back(make_pair(1, 7));
    path.push_back(make_pair(0, 7));
    path.push_back(make_pair(0, 8));
    path.push_back(make_pair(0, 9));
}

Map::Map(QString filename)
{
    // 通过一个txt文件来初始化地图，要求为分号分隔每个坐标,坐标内部逗号分隔，一行输入，表示敌方从开始到结束的路径(地面单位)
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "Can't open the file!" <<endl;
    }
    QTextStream in(&file);
    QString line1 = in.readLine();
    QString line2 = in.readLine();
    string str = line1.toStdString();

    vector<string> sp1 = split(str, ";");
    for (string s : sp1){
        vector<string> point = split(s, ",");
        int x = stoi(point[0]), y = stoi(point[1]), type = stoi(point[2]);
        map[x][y] = type;
    }

    str = line2.toStdString();
    vector<string> sp2 = split(str, ";");
    for (string s : sp2){
        vector<string> point = split(s, ",");
        int x = stoi(point[0]), y = stoi(point[1]);
        path.push_back(make_pair(x, y));
    }
}

vector<string> split(const string &str, const string &pattern)
{
    vector<string> res;
    if(str == "")
        return res;
    //在字符串末尾也加入分隔符，方便截取最后一段
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}
