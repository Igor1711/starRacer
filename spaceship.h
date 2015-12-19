#ifndef SPACESHIP_H
#define SPACESHIP_H

class spaceship
{
public:
    int sx, sy, sz, angle, angle1; //Местонахождение и углы разворота
    short maximumspeed, accel, acceleration; //Максимальная скорость и ускорение.
    float speed;
    int speedx, speedy, speedz; //Текущая скорость общая и по осям.
    spaceship();
    void running(bool obj);
};
class My_ship : public spaceship
{
public:
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
    My_ship(){}
    My_ship(short cor, unsigned int price1);
    void upgrade(short a, short price1);
    void charging();
    void rocketshot();
    void rotatecanon(int s);
    void podbit(short n, short an);
    void lasershot();
    void driving(bool fw, bool bw, bool up, bool down, bool left, bool right);
    void change_camera();
};

class Opponent : public spaceship
{
protected:
    int health, shield;
    int armlase, laserturel, las2, hardness;
public:
    int turns, points, turnan,lap, accel;
    int rcanon, type; float akkcharge;
    short int rockets, rocket_charge;
    bool firster, finished, rshot,lshot, r_ready, l_ready;
    Opponent(int x, int y, int z, int h);
    void traektory_count(int x, int y, int z);
    void podbit(int n, int an);
    int get_params(int p);
    void shoot(int w);
    void charge();
};
class NPC : public spaceship
{

};

#endif // SPACESHIP_H
