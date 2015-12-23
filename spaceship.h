#ifndef SPACESHIP_H
#define SPACESHIP_H
//#include <gameplay.h>


class spaceship
{

protected:
    int sx, sy, sz, angle, angle1; //Местонахождение и углы разворота
    short maximumspeed, accel, acceleration; //Максимальная скорость и ускорение.
    float speed;
    int speedx, speedy, speedz; //Текущая скорость общая и по осям.
    void running(bool obj);
public:
    spaceship();

};
class My_ship : protected spaceship
{
    friend class gameplay;
    friend class gameform;
    friend class Garage;
    friend class Form;
    friend class comp;

protected:
    char *type;//название
    short int laserweapon, camera, tip; //тип лазерного оружия (0 - нет), здоровье, камера, тип корабля (модель корпуса), текущая стоимость
    int price;
    float health, shield;
    float buttery_charge; //заряд батареи.
    short int armlaser,  rockets, lost_control; //заряд лазерной пушки, силового поля, количество оставшихся ракет, потеря управления если подбит
    short int canonangle, anglesc;//угол поворота лазерной турели, угол камеры относительно корабля
    short rockshot;
    bool upgrades[9];
    bool laseshot, hyperjump, activeshield;
    void upgrade(short a, short price1);
    void charging();
    void rocketshot();
    void rotatecanon(int s);
    void podbit(short n, short an);
    void lasershot();
    void driving(bool fw, bool bw, bool up, bool down, bool left, bool right);
    void change_camera();
public:
    My_ship(){}
    My_ship(short cor, unsigned int price1);
};

class Opponent : protected spaceship
{
    friend class gameplay;
    friend class gameform;
    friend class Garage;
    friend class Form;

protected:
    int health, shield;
    int armlase, laserturel, las2, hardness;

    int turns, points, turnan,lap, accel;
    int rcanon, type; float akkcharge;
    short int rockets, rocket_charge;
    bool firster, finished, rshot,lshot, r_ready, l_ready;

    void traektory_count(int x, int y, int z);
    void podbit(int n, int an);
    int get_params(int p);
    void shoot(int w);
    void charge();
public:
    Opponent(int x, int y, int z, int h);
};
class NPC : public spaceship
{

};


#endif // SPACESHIP_H
