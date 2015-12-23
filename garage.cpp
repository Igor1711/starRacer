#include "garage.h"
#include <QQmlContext>
Garage::Garage(QWidget *s, gameplay *g)
{
    Init();
    start = s;
    game = g;
    this->showFullScreen();
}

Garage::~Garage()
{
    delete this;
}
void Garage::Init()
{
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QUrl::fromLocalFile("Garageform.qml"));
    //Root = this->rootObject();       //Соединяем C++ и QML, делая видимым функции С++ через элемент window
    this->rootContext()->setContextProperty("window", this);
}

void Garage::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Escape)
    {
        start->showFullScreen();
        this->close();
    }

}
void Garage::switchcomp_on()
{
    computer=new comp(this, game, false);
    computer->show();
    this->hide();
}
QString Garage::give_info(int param)
{
    switch (param) {
        case 0:
    {
            if (game->space==NULL) return "You don't have a spaceship";
            else return (game->space->type);
            break;
    }
    case 1:
    {
        if (game->space==NULL) return " ";
        else return ("Maximumspeed: "+QString::number(game->space->maximumspeed));
    }
    case 2:
    {
        if (game->space==NULL) return " ";
        else return ("Price to sell: $ "+QString::number(game->space->price));
    }

        default:
    {
        return (QString::number(ret()));
            break;
        }
    }

}
int Garage::ret()
{
    if (game->space==NULL || game->just_bought==true) return -10;
    else return 2;
}



bool Garage::deliver_ship()
{
    if (game->just_bought)
    {
        game->just_bought=false;
        return true;
    }
    else return false;
}

int Garage::get_ship_params(short n)
{
    if (game->space!=NULL)
    {
        switch (n)
        {
            case 0://canon x
            {
                switch (game->space->tip) {
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
                switch (game->space->tip) {
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
                switch (game->space->tip) {
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
QString Garage::get_ship_model(short n)
{
    if (game->space!=NULL)
    {
        if (n==0)//выдача файла 3д модели корабля
        {
            switch (game->space->tip){
            case 1:
                return "./3dmodels/spaceships/pacer.3ds";
            case 2:
                return "./3dmodels/spaceships/gazlock.3ds";
            case 3:
                return "./3dmodels/spaceships/cutter.3ds";
            case 4:
                return "./3dmodels/spaceships/shark.3ds";
            case 5:
                return "./3dmodels/spaceships/spider.3ds";
            default:
                return "./3dmodels/spaceships/pacer.3ds";
            }
        }
        else if (n==1)//выдача файла 3д модели лазерной пушки
        {
            switch (game->space->laserweapon){
            case 0:
                return "./3dmodels/spaceships/nogun.3ds";
            case 1:
                return "./3dmodels/spaceships/lasegun.3ds";
            case 2:
                return "./3dmodels/spaceships/doublegun.3ds";
            default:
                return "./3dmodels/spaceships/nogun.3ds";
            }
        }
        else//и гипердвигателя
        {
            if (game->space->upgrades[2]) return "./3dmodels/spaceships/hiperengine.3ds";
            else return "./3dmodels/spaceships/nogun.3ds";
        }
    }
    else return "./3dmodels/spaceships/nogun.3ds";
}

bool Garage::change_ship()//смена корабля
{
    if (game->my_ship_num > 1)//если у игрока больше одного корабля
    {
        game->my_garage[game->choosen_ship] = game->space;//текущий корабль встает в гараж
        if (game->choosen_ship == 0){//если он первый в списке
            game->choosen_ship = game->my_ship_num - 1;//выбираем последний корабль
        }
        else game->choosen_ship--;//иначе предыдущий
        game->space = game->my_garage[game->choosen_ship];//устанвливаем выбранный корабль текущим
        return true;
    }
    else return false;//смена успешна или менять не на что
}
void Garage::fly_out()//вылет
{
    if (game->space!=NULL)//только если у игрока есть корабль
    {
        city = new gameform(game, this, computer);
        city->showFullScreen();
        this->hide();//загружаем основную игровую форму.
    }
}
