#ifndef TRACK_H
#define TRACK_H
#include <spaceship.h>
#include <QtGui>
//#include <QtCore>

class checkpoint//контрольная точка
{
public:
    short int x, y, z, angle;
    checkpoint(short int x1, short int y1, short int z1, short int x2, short int y2);
};

class track//трасса
{
public:
    short int checked, position, lap, opp, alllaps;
    unsigned int ringsize;//размер кольца контрольной точки, влияет на сложность, чем выше уровень сложности,
    //тем кольца меньше и в них труднее попасть
    Opponent *opponent[6];//соперники от одного до 6
    short int prise1, prise2, prise3;//размер приза за 1-е, 2-е и 3-е место
    checkpoint *checks[21];//контрольные точки
    track(short int n, short int lap1, short int opp1);//конструктор
};

#endif // TRACK_H
