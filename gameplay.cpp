#include "gameplay.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct save1
{
    My_ship *space1;
    int mon;
    int tournament_progress;
};

gameplay :: gameplay(bool load)
{
    money = 48000;//изначальное количество денег, при начале новой игры
    finished = 0;
    tournament_progress = 0;
    my_ship_num = 0;
    choosen_ship = 0;//Изначально нет кораблей
    tournament = 0;
    started = false;
    x = 0; y = 0; z = 0; just_bought = false;
    space = NULL; race = NULL;
    trackloaded = false; finished = false;
    good[0] = new item(1, 38000, "pacer DH-100", "A fast and economic spaceship. \n maximumspeed 3000, weapon - rockets \n hiperengine - optional");
    good[1] = new item(1, 40500, "gazlock SD300", "Heavy race-ship, shield in complect slower than pacer but accelerates faster \n maximumspeed 2900, weapon - rockets \n hiperengine - optional");
    good[2] = new item(1, 53000, "CutterMil1", "Race-version of police ship, has larger butterys and shield-in-complect secret technologies encreased the acceleration, best choice for difficult tracks\n maximumspeed 6500, weapon - rockets \n hiperengine - optional");
    good[3] = new item(1, 52000, "Shark SD-360", "Very fast spaceship, has an upgraded engine and larger butterys from the production line , weapon - rockets \n hiperengine optional");
    good[4] = new item(1, 56500, "Spider SRH250", "New technology allows to reach better characterics for the same resources, this spaceship has an upgraded engine and larger butterys from the production line also it is 500mph faster than based ships with such engines, best for straight tracks, weapon - rockets \n hiperengine optional");
    good[5] = new item(2, 12000, "ForsedH-200", "Forsed Engine will encrease your result");
    good[6] = new item(2, 17000, "NitroForceHN-500", "New NitroHidragenium engines will double your speed");
    good[7] = new item(2, 33000, "HiperSDH-5000", "Hiperengine opens other planets");
    good[8] = new item(2, 3800, "Shield-150", "Protecting shield");
    good[9] = new item(2, 3500, "ButteryX2", "Forced akkumulator charges lasers faster");
    good[10] = new item(2, 10500, "Radar", "Using a radar you can easily find the next checkpoint if ypu missed it \n Also on a Radar you can see where ypur opponents are, Radar is necessary to fulfill quests");
    good[11] = new item(2, 4900, "Lasergun S-50", "lasergun doesn't need charges");
    good[12] = new item(2, 9000, "Lasergun DS-100", "Double canon - double damage");
    good[13] = new item(2, 5000, "RX-30", "this robot saves you $100/ upgrade");
    //loadborders();
    place[0].x = 17397; place[0].z = 47900; place[0].y = 114884;
    place[1].x = -64282; place[1].z = 47900; place[1].y = 35311;
    place[2].x = -64282; place[2].z = 47900; place[2].y = 35311;
    part_in_single = false;// участие в одиночном заезде, оружие отключено
    if (load) load_game();
    count = 0; min = 0; sec = 0; mil = 0; //пока игрок не участвует в гонке таймер обнулен
}

void gameplay :: loadtrack(int number, int lap, int opp)
{
    finished1=0;
    race=new track(number, lap,opp);
    int hard;
    started=true;
    int i=0;
    while (i<6)
    {
        race->opponent[i]=NULL;
        i++;
    }
    i=0;
    while (i<race->opp)
    {
        switch (tournament) {
            case 1:{
                hard=1;
                break;
            }
            case 2:{
                hard=1+(rand() %2);
                break;
            }
            case 3:{
                hard=2+(rand() %2);
                break;
            }
            case 4:{
                hard=3;
                break;
            }
            default:{
                switch (number){
                case 1:{
                    hard=1+(rand() %2);
                    break;
                }
                case 2:{
                    hard=2;
                    break;
                }
                case 3:{
                    hard=2+(rand() %2);
                    break;
                }
                default: {hard = 1;
                    break;
                }
                }
                break;
            }
        }
        race->opponent[i]=new Opponent(place[1].x,place[1].y-600*i,place[1].z,hard);
        i++;
    }
    for (i=0; i<race->opp; i++)
    {
        race->opponent[i]->sx=place[1].x+600*cos(3.14*i);
        race->opponent[i]->sy=place[1].y-600*i;
        race->opponent[i]->sz=place[1].z;
    }
    space->sx=place[2].x+600*cos(3.14*i);
    x=place[1].x/100;
    space->sz=place[2].z;
    z=place[1].z/100;
    space->sy=place[2].y-600*i;
    y=place[1].y/100;
    space->angle=90;
    space->angle1=0;
    space->speed=0;
    count=60;
    min=0; sec=0; mil=0;
    race->ringsize = 30 - (5*hard);
    trackloaded=true;

}
void gameplay :: loadfinish()
{
    trackloaded=false;
}
void gameplay :: checking()
{
    int sx, sy, sz,i;
    float size;
    if (race == NULL) size = 1;
    else size = race->ringsize/10;
    sx = space->sx/100;
    sy = space->sy/100;
    sz = space->sz/100;
    if (started)
    {
        int x1,y1,z1;
        bool check = false;
        x1 = race->checks[race->checked]->x;
        y1 = race->checks[race->checked]->y;
        z1 = race->checks[race->checked]->z;
        if ((x <= (x1-(35*size)) && sx > (x1-(35*size))) && (sy>=(y1-(35*size)) && sy<=(y1+(35*size))) && (sz>=(z1-(35*size)) && sz<=(z1+(35*size)))) check=true;
        if ((x >= (x1+(35*size)) && sx < (x1+(35*size))) && (sy>=(y1-(35*size)) && sy<=(y1+(35*size))) && (sz>=(z1-(35*size)) && sz<=(z1+(35*size)))) check=true;
        if ((y <= (y1-(35*size)) && sy > (y1-(35*size))) && (sx>=(x1-(35*size)) && sx<=(x1+(35*size))) && (sz>=(z1-(35*size)) && sz<=(z1+(35*size)))) check=true;
        if ((y >= (y1+(35*size)) && sy < (y1+(35*size))) && (sx>=(x1-(35*size)) && sx<=(x1+(35*size))) && (sz>=(z1-(35*size)) && sz<=(z1+(35*size)))) check=true;
        if ((z <= (z1-(35*size)) && sz > (z1-(35*size))) && (sy>=(y1-(35*size)) && sy<=(y1+(35*size))) && (sx>=(x1-(35*size)) && sx<=(x1+(35*size)))) check=true;
        if ((z >= (z1+(35*size)) && sz < (z1+(35*size))) && (sy>=(y1-(35*size)) && sy<=(y1+(35*size))) && (sx>=(x1-(35*size)) && sx<=(x1+(35*size)))) check=true;
        if (check) race->checked++;
        if (race->checked>19)
        {
            race->lap++;
            if (space->rockets<18) space->rockets=18;
            race->checked=0;
        }
        if (race->lap>race->alllaps && space->sy>39500)
        {
            started=false; finished=true; space->speed=0; part_in_single=false;
            table_write(0);
            if (race->position == 1 && race->opp!=0) money += race->prise1;
            if (race->position == 2) money += race->prise2;
            if (race->position == 3) money += race->prise3;
            i=0;
            while (i<race->opp)
            {
                race->opponent[i]=NULL;
                i++;
            }
            part_in_single=false;
        }
    }
    x = space->sx/100;
    y = space->sy/100;
    z = space->sz/100;
}

void gameplay :: tournament_start()
{
    rest_races -= 1;
    if (tournament  ==  1) loadtrack(0, 3, 5);
    if (tournament  ==  2) loadtrack(2, 3, 5);
    if (tournament  ==  3) loadtrack(1, 3, 5);
    if (tournament  ==  4) loadtrack(2, 3, 5);
    race->prise1 = 0;
    race->prise2 = 0;
    race->prise3 = 0;
}
void gameplay :: tournament_continue()
{
    //short int posit;
    if (rest_races > 0)
    {
        if (tournament  ==  1)
        {
            loadtrack(1, 3, 5);
        }
        if (tournament  ==  2)
        {
            if (rest_races  ==  2) loadtrack(1, 3, 5);
            if (rest_races  ==  1) loadtrack(3, 3, 5);
        }
        if (tournament  ==  3)
        {
            if (rest_races  ==  3) loadtrack(3, 3, 5);
            if (rest_races  ==  2) loadtrack(0, 3, 5);
            if (rest_races  ==  1) loadtrack(2, 3, 5);
        }
        if (tournament  ==  4)
        {
            if (rest_races  ==  3) loadtrack(1, 4, 5);
            if (rest_races  ==  2) loadtrack(0, 4, 5);
            if (rest_races  ==  1) loadtrack(3, 4, 5);
        }
    }
    else tournament_finish();
    race->prise1 = 0;
    race->prise2 = 0;
    race->prise3 = 0;
    rest_races -= 1;
}
short int gameplay  ::  tournament_finish()
{
    short int pos = 6;
    short int i = 1;
    while (i < 6)
    {
        if (tournament_table[0] >= tournament_table[i]) pos--;
        i++;
    }
    tournament = 0;
    return pos;
}
void gameplay :: save_game()
{
    FILE *f;
    f=fopen ("savefile.txt", "wt");
    char s1[20];
    sprintf (s1, "%d|", my_ship_num);
    fputs (s1, f);
    fputs("/", f);
    for (int j = 0; j < my_ship_num; j++)
    {
        sprintf (s1, "%d|", my_garage[j]->tip);
        fputs (s1, f);
        strncpy(s1, ":", 1);
        int i = 1;
        while (i < 10)
        {
            if (my_garage[j]->upgrades[i - 1]) s1[i] = 'r';
            else s1[i] = 'w';
            i++;
        }
        s1[i] = '\0';
        fputs(s1, f);
        fputs("/", f);
    }
    sprintf(s1, ">%d", money);
    fputs(s1, f);
    sprintf(s1, "<%d", tournament_progress);
    s1[24] = '\0';
    fputs(s1, f);
    fputs("\n", f);
    fclose(f);
}
void gameplay :: load_game()
{
    FILE *f;
    f = fopen ("savefile.txt", "r");
    if (f != NULL)
    {
        char *s1 = (char*) malloc(256), s2[15];
        //Определение количества кораблей в гараже
        int i = 0;
        fgets(s1, 256, f);
        while (s1[i] != '|' && s1[i] != '\0')
        {
            s2[i] = s1[i];
            i++;
        }
        s2[i] = '\0';
        my_ship_num = atoi(s2);
        int j = 0;
        while (j < my_ship_num)//определяем корабли
        {
            s1 = strchr(s1,'/') + 1;
            i = 0;
            while (s1[i] != '|' && s1[i] != '\0')
            {
                s2[i] = s1[i];
                i++;
            }
            s2[i] = '\0';
            int type = atoi(s2);
            my_garage[j] = new My_ship(type, good[type-1]->price);
            s1 = strchr(s1,'|') + 2;
            for (i = 0; i < 9; i++)
            {
                if (s1[i]  ==  'r' && !my_garage[j]->upgrades[i]) my_garage[j]->upgrade(i, good[i + 5]->price);
            }
            j++;
        }
        s1 = strchr(s1, '>') + 1;

        money = atoi(s1);//баланс игрока
        s1 = strchr(s1, '<') + 1;
        tournament_progress = atoi(s1);//прогресс игрока
        space = my_garage[0];
        fclose(f);
    }

}

void gameplay :: opponent_shoot(int n)
{
    int x1, y1, z1;
    x1 = race->opponent[n]->sx;
    y1 = race->opponent[n]->sy;
    z1 = race->opponent[n]->sz;
    short int i11;
    i11 = 0;
    aim_oppon(x1, y1, z1, race->opponent[n]->angle, race->opponent[n]->angle1, space->sx, space->sy, space->sz);
    if (tx < 400 && tx>-400 && ty<400 && ty>-400 && tz>-1000 && tz<1000)
    {
        if (race->opponent[n]->r_ready)
        {
            race->opponent[n]->shoot(3);
            if (tx<200 && tx>-200 && ty<200 && ty>-200 && tz>-600 && tz<600) space->podbit(3, ty);
        }
        else
        {
            if (race->opponent[n] -> l_ready && race->opponent[n]->get_params(5)>1)
            {
                race->opponent[n] -> shoot(1);
                if (tx<200 && tx>-200 && ty<200 && ty>-200 && tz>-600 && tz<600) space->podbit((race->opponent[n]->get_params(5)-1), 0);
            }
        }
    }
    while (i11<race->opp)
    {
         if (i11!=n)
         {
              aim_oppon(x1,y1,z1,race->opponent[n]->angle, race->opponent[n]->angle1,race->opponent[i11]->sx,race->opponent[i11]->sy,race->opponent[i11]->sz);
              if (tx<400 && tx>-400 && ty<400 && ty>-400 && tz>-1000 && tz<1000)
              {
                  if (race->opponent[n]->r_ready)
                  {
                      race->opponent[n]->shoot(3);
                      if (tx<200 && tx>-200 && ty<200 && ty>-200 && tz>-600 && tz<600) race->opponent[i11]->podbit(3,tx);
                  }
                  else
                  {
                      if (race->opponent[n]->l_ready && (race->opponent[n]->get_params(5)>1))
                      {
                          race->opponent[n]->shoot(1);
                          if (tx<200 && tx>-200 && ty<200 && ty>-200 && tz>-600 && tz<600) race->opponent[i11]->podbit((race->opponent[n]->get_params(5)-1),tx);
                      }
                  }
              }
         }
         i11++;
    }
}

void gameplay::opponent_driving()
{
    int x1,y1,z1,p1,s1,s2, i;
    i=0;
    while (i<race->opp)
    {
        race->opponent[i]->charge();
        p1=race->opponent[i]->points;
        x1=race->checks[p1]->x;
        y1=race->checks[p1]->y;
        z1=race->checks[p1]->z;
        race->opponent[i]->traektory_count(x1,y1,z1);
        if (sqrt((x1-race->opponent[i]->sx/100)*(x1-race->opponent[i]->sx/100)+(y1-race->opponent[i]->sy/100)*(y1-race->opponent[i]->sy/100))<(15+race->opponent[i]->speed/100))
        {
            race->opponent[i]->points++;
        }
        if (race->opponent[i]->points>19)
        {
            race->opponent[i]->lap++; race->opponent[i]->points=0;race->opponent[i]->rockets=18;
        }
        if (race->opponent[i]->lap>race->alllaps && race->opponent[i]->sy>39500)
        {
            race->opponent[i]->speed=0; race->opponent[i]->points=5;
            table_write(i+1);
            race->opponent[i]->finished=true;
        }
        if (race->opponent[i]->lap>race->lap) race->opponent[i]->firster=true;
        if (race->opponent[i]->lap<race->lap) race->opponent[i]->firster=false;
        if (race->opponent[i]->lap == race->lap)
        {
            if (race->opponent[i]->points>race->checked) race->opponent[i]->firster=true;
            if (race->opponent[i]->points<race->checked) race->opponent[i]->firster=false;
            if (race->opponent[i]->points == race->checked)
            {
               s1=sqrt((space->sx-x1)*(space->sx-x1)+(space->sy-y1)*(space->sy-y1)+(space->sz-z1)*(space->sz-z1));
               s2=sqrt((race->opponent[i]->sx-x1)*(race->opponent[i]->sx-x1)+(race->opponent[i]->sy-y1)*(race->opponent[i]->sy-y1)+(race->opponent[i]->sz-z1)*(race->opponent[i]->sz-z1));
               if (s1<=s2) race->opponent[i]->firster=false;
               else race->opponent[i]->firster=true;
            }
        }
        race->opponent[i]->running(false);
        if (part_in_single == false && (race->opponent[i]->r_ready || race->opponent[i]->l_ready)) opponent_shoot(i);
        i++;
    }
    race->position=1;
    i=0;
    while (i<race->opp)
    {
        if (race->opponent[i]->firster) race->position++;
        i++;
    }
}
void gameplay::timer1()
{
    if (started)
    {
        mil += 4;
        if (mil>=100)
        {
            sec += 1;
            mil-=100;
        }
        if (sec>=60)
        {
            min += 1;
            sec-=60;
        }
    }
}



void gameplay::aim_oppon(int cx, int cy, int cz, int aim1, int aim2, int ax, int ay, int az)
{
    int disx, disy, disz, distance, realax, realay, realaz;
    disx=cx-ax;
    disy=cy-ay;
    disz=cz-az;
    distance=sqrt((disx*disx)+(disy*disy)+(disz*disz));
    realax=cx-distance*cos(6.28*aim1/360)*cos(6.28*aim2/360);
    realay=cy+distance*sin(6.28*aim1/360)*cos(6.28*aim2/360);
    realaz=cz+distance*sin(6.28*aim2/360);
    tx=realax-ax;
    ty=realay-ay;
    tz=realaz-az;
}
void gameplay::player_shot(int a)
{
    int i;
    bool armed = false;
    int weapon = 0;
    if (a == 1)
    {
        space->lasershot();
        armed = space->laseshot;
        weapon = space->laserweapon;
    }
    else
    {
        if (space->rockets>0)
        {
            space->rocketshot();
            armed = true;
            weapon = 3;
        }
    }
    if (armed)
    {
        i=0;
        if (race!=NULL)
        {
        while (i<race->opp)
        {
            aim_oppon(space->sx,space->sy,space->sz,space->angle+space->canonangle,space->angle1,race->opponent[i]->sx,race->opponent[i]->sy,race->opponent[i]->sz);
            if (tx<200 && tx>-200 && ty<200 && ty>-200 && tz<600 && tz>-600)
            {
                race->opponent[i]->podbit(weapon, tx);
                break;
            }

            i++;
        }
        }
    }
}
void gameplay::table_write(short n)
{

    if (tournament>0)
    {
        if (n == 0)
        {
            tournament_table[0] += (10 - (finished1 * 2));
            finished1++;
            short int i = 0;
            while (i<race->opp)
            {
                if (race->opponent[i]->finished == false)
                {
                    tournament_table[i+1] += (10 - (finished1 * 2));
                    race->opponent[i]->finished = true;
                    finished1++;
                }
                i++;
            }
        }
        else
        {
            if (race->opponent[n-1]->finished == false)
            {
                tournament_table[n] += (10 - (finished1 * 2));
                finished1++;
            }
        }
    }

}
int gameplay::get_ship_params(short n)
{
    if (space!=NULL)
    {
        switch (n)
        {
            case 0://canon x
            {
                switch (space->tip) {
                case 1:
                   return 0;
                case 2:
                    return 150;
                case 3:
                    return 150;
                case 4:
                    return 0;
                case 5:
                    return 120;
                default:
                    return 0;
                }
            }
            case 1://canon y
            {
                switch (space->tip) {
                case 1:
                   return 20;
                case 2:
                    return 0;
                case 3:
                    return 0;
                case 4:
                    return 15;
                case 5:
                    return 5;
                default:
                    return 0;
                }
            }
            case 2://hiperengine x
            {
                switch (space->tip) {
                case 1:
                   return 0;
                case 2:
                    return 50;
                case 3:
                    return 150;
                case 4:
                    return 150;
                case 5:
                    return 30;
                default:
                    return 0;
                }
            }
        default:
            return 0;
        }
    }
    else return 0;
}
QString gameplay::get_ship_model(short n)
{
    QString catalog = "./3dmodels/spaceships/";
    if (space!=NULL)
    {
        if (n==0)
        {
            switch (space->tip){
            case 2:
                return catalog+"gazlock.3ds";
            case 3:
                return catalog+"cutter.3ds";
            case 4:
                return catalog+"shark.3ds";
            case 5:
                return catalog+"spider.3ds";
            default:
                return catalog+"pacer.3ds";
            }
        }
        else if (n==1)
        {
            switch (space->laserweapon){
            case 1:
                return catalog+"lasegun.3ds";
            case 2:
                return catalog+"doublegun.3ds";
            default:
                return catalog+"nogun.3ds";
            }
        }
        else
        {
            if (space->upgrades[2]) return catalog+"hiperengine.3ds";
            else return catalog+"nogun.3ds";
        }
    }
    else return "./3dmodels/spaceships/nogun.3ds";
}


