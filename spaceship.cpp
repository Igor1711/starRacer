#include "spaceship.h"
#include "math.h"
#include "time.h"
#include <cstdlib>

spaceship :: spaceship()
{
    sx = 0;
    sy = 0;
    speed = 0;
    speedx = 0; speedy = 0; speedz = 0;
    maximumspeed = 3000;
    angle1 = 0;
    angle = 0;
    accel = 0;
    acceleration = 0;
}

void spaceship :: running(bool obj)
{
    speed += acceleration;
    speedx = ((speed * cos(6.28 * angle / 360))) * cos(6.28 * angle1 / 360);
    sx -= speedx;
    speedy = ((speed * sin(6.28 * angle / 360))) * cos(6.28 * angle1 / 360);
    sy += speedy;
    speedz = ((speed * sin(6.28 * angle1 / 360)));
    if (obj) sz -= speedz;
    else sz +=speedz;
}

My_ship :: My_ship(short cor, unsigned int price1) : spaceship()
{
    buttery_charge = 100;
    rockets = 18;
    anglesc = 0;
    hyperjump = false;
    health = 100;
    price = price1 - 2000;
    laserweapon = 0;
    armlaser = 0;
    shield = 0;
    lost_control = 0;
    laseshot = false;
    short int i = 0;
    while (i < 9)
    {
        upgrades[i] = false;
        i++;
    }
    accel = 10;
    maximumspeed = 3000;
    if (cor == 1) type = "Pacer";
    if (cor == 2)
    {
        type = "Gazlock";
        upgrade(3, 2000);
        maximumspeed += 100;
        accel -= 1;
    }
    if (cor == 3)
    {
        type = "Cutter";
        upgrade(0, 2000);
        upgrade(3, 2000);
        accel += 3;
        maximumspeed -= 50;
    }
    if (cor == 4)
    {
        type = "Shark";
        upgrade(0, 2000);
        upgrade(3, 2000);
        maximumspeed += 300;
    }
    if (cor == 5)
    {
        type = "Spider SRH250";
        upgrade(0, 2000);
        upgrade(3, 2000);
        maximumspeed += 500;
        accel -= 2;
    }

    tip = cor;
    canonangle = 0;
    camera = 0;
    rockshot = 1;
    acceleration = 0;
}


void My_ship :: upgrade(short a, short price1)
{
    upgrades[a] = true;//апгрейд установлен
    price += (price1 - 2000);
    if (a == 0)
    {
        accel += 4;
        maximumspeed += 2000;
    }
    if (a == 1)//увеличение мощности двигателя
    {
        accel += 4;
        maximumspeed += 2500;
    }
    if (a == 6)
    {
        if (laserweapon == 2)//установка пушки
        {
            upgrades[7] = false;
            price -= 5000;
        }
        laserweapon = 1;
    }
    if (a == 7)
    {
        if (laserweapon == 1)//установка двойной пушки
        {
            upgrades[6] = false;
            price -= 800;
        }
        laserweapon = 2;
    }

}

void My_ship::driving(bool fw, bool bw, bool up, bool down, bool left, bool right)
{
    if (lost_control==0)//если управление не потеряно
    {
        if (fw && speed < maximumspeed) acceleration = accel + (rand() % 4);//если не достигнута максимальная скорость, разгоняемся
        if (bw && speed > 0) acceleration = (-1.5 * accel);//торможение
        if (bw && speed <= 0 && speed>-100) acceleration = -2;//задний ход
        if ((bw && speed <= -100) || (fw && speed>maximumspeed)) acceleration = 0;//при максимальной скорости ускорение 0
        if (left)
        {
            if (anglesc<12) anglesc+=1;
            angle+=6;//управление и поворот модели корабля на экране
        }
        if (right)
        {
            if (anglesc>-12) anglesc-=1;
            angle-=5;
        }
        if (!left && !right)
        {
            if (anglesc > 0) anglesc -= 1;
            if (anglesc < 0) anglesc += 1;
        }//когда руль отпущен, модель на экране выравнивается
        if (!fw && !bw)
        {
            if (speed > 100) acceleration = -accel / 2;
            if (speed > 0 && speed<100) acceleration = -2;
            if (speed < 0) acceleration = 1;
        }//корабль замедляется при отпущенном газе
    }
    else
    {
        lost_control -= 1;
        angle += 10;
    }//потеря управления при попадании ракеты соперника
    if (health <= 0) speed = 0;//если здоровье 0, двигатели отключаются
    if (up) angle1 -= 5;//
    if (down) angle1 += 5;//вверх вниз
    if (angle1 > 180) angle1 -= 360;
    if (angle1 <- 180) angle1 += 360;//значение угла поворота : [-180..180]
    running(true);//движение корабля
}


void My_ship::charging()//зарядка батарей и устройств
{
    if (buttery_charge > 0)//замряд аккумулятора
    {
        if (armlaser < 100 && laserweapon != 0)
        {
            armlaser += 1;//заряжаем лазер
            if (upgrades[5])
            {
                armlaser += 1;//если аккумуляторы прокачены, скорость заряда увеличивается
                buttery_charge -= 0.1;
            }
            else buttery_charge -= 0.2;//расход заряда улучшенного и обчного аккумулятора
        }
        if (shield < 100 && activeshield == false && upgrades[3])
        {
            shield += 1;//заряжаем силовое поле
            if (upgrades[5]) buttery_charge -= 0.1;
            else buttery_charge -= 0.2;
        }
    }
    if (activeshield)
    {
        if (shield > 0) shield -= 0.2;
        else activeshield = false;//активированное силовое поле разряжается само
    }
    if (upgrades[8] && health < 100) health += 0.2; //робот чинит корабль
    if (buttery_charge < 100)
    {
        if (upgrades[5]) buttery_charge += 0.3;
        else buttery_charge += 0.1;//заряжаем аккумуляторы
    }

}

void My_ship :: rocketshot()//выстрел ракетой
{
    rockets -= 1;// - 1 ракета
    rockshot += 10;//время перезарядки ракетницы
}

void My_ship::lasershot()//выстрел лазером
{
    if (armlaser == 100)//если лазер заряжен
    {
        armlaser = 0;//разряд лазера при выстреле
        laseshot = true;//выстрел
    }
}

void My_ship :: podbit(short n, short an)//подбит
{
    int hit;//урон
    hit = 10 * n;//размер урона
    shield -= hit;//силовое поле гасит урон
    if (shield < 0)
    {
       health += shield;
       shield = 0;//если силовое поле израсходовано, корабль получает урон
       if (health < 0) health = 0;//здоровье - положительное число
       if (n == 3)
       {
           if (an > 0) lost_control = an / 10;//если попадание ракетой, потеря управления на определённый срок
           else lost_control = -an / 10;
       }
    }//если ракета попала в защитное поле, то взрывная волна не чувствуется

}

Opponent :: Opponent(int x, int y, int z, int h)
{
    spaceship();
    sx = x; sy = y; sz=z; angle=90; angle1=0; //установка местоположения
    laserturel = h; //тип лазерной пушки (нет, одинарная или спаренная)
    points = 0; //изначально не пройдено контрольных точек
    lap = 1; //изначально первый круг гонки
    rockets = 18 + (3 * h); //количество ракет зависит от уровня сложности
    rocket_charge = 40; akkcharge = 100; armlase = 0; rshot = false; lshot = false; //задержка при старте и изначальные параметры заряда
    r_ready = false; l_ready = false; //изначально оружие не готово
    hardness=h; //уровень сложности
    maximumspeed=2000 * h + 1000;
    if (h == 3) maximumspeed = 7500; //максимальная скорость зависит от уровня сложности
    finished = false; //не финишировал изначально.
}

int Opponent::get_params(int p) //запрос параметров
{
    if (p == 0) return sx;
    if (p == 1) return sz;
    if (p == 2) return sy;
    if (p == 3) return angle;
    if (p == 4) return -angle1;
    if (p == 5) return hardness;
    else return 0;
}

void Opponent::traektory_count(int x, int y, int z)
{
    float sl = sqrt((x - sx / 100) * (x - sx / 100) + (y - sy / 100) * (y - sy / 100));
    if (sl < 10) sl = 10;
    float sl1 = sqrt((x - sx / 100) * (x - sx / 100) + (z - sz / 100) * (z - sz / 100));
    if (sl1 < 10) sl1 = 10;
    int a1;
    if ((y - sy / 100) > 0) a1 = 180 - 360 * (acos((x - sx / 100) / sl)) / 6.28;
    else a1 = 360 * (acos((x - sx / 100) / sl)) / 6.28 - 180;
    short int acelerate;
    acelerate = 4 * hardness + 5;
    int a2 = 360 * asin((z - sz / 100) / sl1) / 6.28; //определяем углы направления на цель
    if (angle > a1)
    {
        if (speed > 500) speed -= acelerate;
        if ((angle - 180) > a1) angle -= 360;
        if ((angle - 5) > a1) angle -= 5;
        else angle = a1;
    }
    if (angle < a1)
    {
        if (speed > 500) speed -= acelerate;
        if ((angle + 180) < a1) angle += 360;
        if ((angle + 5) < a1) angle += 5;
        else angle = a1;
    }
    if (angle1 > a2)
    {
        if (speed > 350) speed -= acelerate;
        if ((angle1 - 180) > a2) angle1 -= 360;
        if ((angle1 - 6) > a2) angle1 -= 6;
        else angle1 = a2;
    }
    if (angle1 < a2)
    {
        if (speed > 350) speed -= acelerate;
        if ((angle1 + 180) < a2) angle1 += 360;
        if ((angle1 + 6) < a2) angle1 += 6;
        else angle1 = a2;
    }//поворот в сторону цели со снижением скорости
    if ((angle == a1 && angle1 == a2 && speed < maximumspeed) || speed < 500)
    {
        accel = (acelerate + (rand() % 6 ));
        //if (health > 0)
            speed += accel;//двигатель отключается при отсутствии здоровья
        //else speed = 0;
    }

}

void Opponent::podbit(int n, int an)
{
    int hit; //урон сопернику от различных видов оружия
    hit=10 * n;
    angle1 += 5 * n; //сбивание с курса при попадании
    shield -= hit; //силовое поле гасит урон
    if (shield < 0)
    {
        if (hardness == 3) health += shield / 2; //броня соперников 3-го уровня гасит урон
        else health += shield / 2; //если силовое поле выработано корабль получает урон
        shield = 0;
        if (n == 3)
        {
            angle += an; //разворот взрывной волной от ракеты
            speed -= 200; //сброс скорости при попадании
        }
    }
}

void Opponent::shoot(int w)
{
    if (w < 3)
    {
        if (armlase >= 100)//выстрел только когда лазер накопил заряд
        {
            lshot = true;
            armlase = 0;
            l_ready = false;
        }
    }
    if (w == 3)
    {
        if (rockets > 0 && rocket_charge <= 0) //выстрел только когда есть ракеты и установка заряжена
        {
            rockets -= 1;
            rocket_charge = 20;
            rshot = true;
            r_ready = false;
        }
    }
}

void Opponent :: charge()//заряд батарей и орудий соперника аналогично кораблю игрока
{
    if (armlase < 100 && akkcharge > 0)
    {
        armlase += 3;
        akkcharge -= 0.9;
    }
    if (armlase >= 100) l_ready = true;
    if (akkcharge < 100) akkcharge += 0.25;
    if (rocket_charge > 0) rocket_charge -= 1;
    if (rocket_charge == 0 && rockets > 0) r_ready = true;
}

void My_ship::change_camera()//смена вида спереди, сзади, справа, слева
{
    camera -= 90;
    if (camera == -360) camera = 0;
}
