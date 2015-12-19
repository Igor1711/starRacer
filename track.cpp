#include "track.h"
#include <math.h>

checkpoint::checkpoint(short x1, short y1, short z1, short x2, short y2)
{
    x = x1; y = y1; z = z1;
    float distance  =  sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));//определение расстояния от предыдущей
    angle = (360*acos((y2-y)/distance)/6.28);//угол поворота на предыдущую к. точку
}


track::track(short n, short lap1, short opp1)
{
    int i = 1;
    alllaps = lap1;//количество кругов
    lap = 1;//текущий круг
    ringsize = 25;//размер кольца
    position = 1;//позиция игрока
    opponent[0]  = NULL;//очистка массива соперников
    checked = 0;//количество пройденных к.т.
    opp = opp1;//количество соперников
    checks[0] = new checkpoint(-674,609,503,-674,495);
    if (n == 1 || n == 2)
    {
         while (i < 10)
         {
             checks[i] = new checkpoint(-674 - 4000 * sin(6.28 * i / 20) * sin(6.28 * i / 20) * sin(6.28 * i / 20), 499 + 5000 * sin(6.28 * i / 20) * sin(6.28 * i / 20) * cos(6.28 * i / 20),-98 + 143 - 450 * sin (6.28 * (18 * i * (2 * n - 1) - 90) / 360), checks[i - 1]->x, checks[i - 1]->y);
             i++;
         }
         while (i < 20)
         {
             checks[i] = new checkpoint(-674-4000*sin(6.28*i/20)*sin(6.28*i/20)*sin(6.28*i/20),499-12000*sin(6.28*i/20)*sin(6.28*i/20)*cos(6.28*i/20),-98+143-450*sin(6.28*(18*i-90)/360),checks[i-1]->x,checks[i-1]->y);
             i++;
         }
         checks[18]->z = 900;
         checks[20] = new checkpoint(-674, -65, 493, checks[i-1]->x,checks[i-1]->y);
         prise1 = 8000;
         prise2 = 0;
         prise3 = 0;
    }
    if (n == 3)
    {
        while (i < 10)
        {
            checks[i] = new checkpoint(-674-40000*sin(6.28*i/20)*sin(6.28*i/20)*sin(6.28*i/20),499+8000*sin(6.28*i/20)*sin(6.28*i/20)*cos(6.28*i/20),-98+143-450*sin(6.28*(18*i*5-90)/360),checks[i-1]->x,checks[i-1]->y);
            i++;
        }
        while (i < 20)
        {
            checks[i] = new checkpoint(-674-40000*sin(6.28*i/20)*sin(6.28*i/20)*sin(6.28*i/20),499-12000*sin(6.28*i/20)*sin(6.28*i/20)*cos(6.28*i/20),-98+143-450*sin(6.28*(18*i*3-90)/360),checks[i-1]->x,checks[i-1]->y);
            i++;
        }
        checks[18]->z = 900;
        checks[20] = new checkpoint(-674, -65, 493, checks[i-1]->x,checks[i-1]->y);
        prise1 = 25000;
        prise2 = 15000;
        prise3 = 8000;
    }

    if (n == 0)
    {
        while (i < 20)
        {
            checks[i] = new checkpoint(-674+1350-(((4700*sin(6.28*i/20)*sin(6.28*i/20))+1300*cos(6.28*i/20)*cos(6.28*i/20))*cos(6.28*i/20)), 499+(4700*sin(6.28*i/20)*sin(6.28*i/20)+1300*cos(6.28*i/20)*cos(6.28*i/20))*sin(6.28*i/20),493,checks[i-1]->x,checks[i-1]->y);
            i++;
        }
        checks[20] = new checkpoint(-674, -65, 493, checks[i-1]->x,checks[i-1]->y);
        prise1 = 5000;
        prise2 = 0;
        prise3 = 0;
    }//загрузка массива к.т. в зависисмости от выбора трассы
    if (n == 2)
    {
        prise1 = 15000;
        prise2 = 5000;
        prise3 = 1500;
    }//Установка размера приза
}
