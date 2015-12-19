#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <spaceship.h>
#include <track.h>
#include <QString>


struct key_position//контрольная точка
{
    int x, y, z;//координаты
};

class item//товар
{
public:
    short int type;//тип корабль/апгрейд
    QString name, use1;//название, описание
    int price;//цена
    item(short int a, int b, QString c, QString d)
    {
        type = a;
        price = b;
        name = c;
        use1 = d;
    }
};

class gameplay
{
public:
    short int my_ship_num;//Количество кораблей в гараже
    short int choosen_ship; //Номер текущего корабля
    My_ship *my_garage[5];//Гараж на 5 кораблей
    short int tournament;//Номер выбранного турнира
    short int tournament_table[6];//турнирная таблица
    short int rest_races;//осталось гонок до конца турнира
    short int finished1;//количество финишировавших соперников
    key_position place[10];//ключевые точки на карте(гараж, стартовая линия и т.д.)
    bool part_in_single;//учавствуем в одиночной гонке, нет оружия
    short int min, sec, mil;//таймер, отсчитывает время заезда
    int money, exp, x, y, z, count;//деньги, опыт, местоположение корабля игрока, таймер отсчета перед гонкой
    bool started, finished;//отмечаем моменты старта и финиша
    My_ship *space;//корабль игрока
    track *race;//трасса
    bool just_bought, trackloaded;//отчет о покупке корабля, загрузке трека
    gameplay(bool load);//конструктор, загружаем сохраненную игру или начинаем новую
    void loadtrack(int number, int lap, int opp);//загрузка трека
    item *good[14];//товары в магазине
    void loadfinish();//окончание загрузки (для взаимодействия с qml-скриптами)
    void checking();//проверка прохождения игрока по трассе
    void opponent_driving();//управление соперниками
    void timer1();//таймер
    void collision(int sx, int sy, int sz);//колизия,
    void aim_oppon(int cx, int cy, int cz, int aim1, int aim2, int ax, int ay, int az);//наведение пушек
    void player_shot(int a);//обработка выстрела игрока
    int tx,ty,tz;//цель орудия
    void tournament_start();//начало турнира
    void tournament_continue();//продолжение турнира
    short tournament_finish();//окончание турнира
    void table_write(short int n);//запись турнирной таблицы
    void save_game();//сохранение игры
    void load_game();//загрузка игры
    void opponent_shoot(int n);//выстрел соперника
    void loadborders();//загрузка базы границ (для коллизий)
    QString get_ship_model(short n);//выдает путь к 3d модели
    int get_ship_params(short n);//выдает размеры корабля

};

#endif // GAMEPLAY_H
