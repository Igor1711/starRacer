#include "gameform1.h"
#include "math.h"
#include <QQmlContext>
int put_in_garage(int n)
{
    int k = 0;
    if (n < 10) k = 0;
    if (n >= 10 && n < 20) k = 10;
    if (n >= 20 && n < 30) k = 20;
    if (n >= 30 && n < 40) k = 30;
    if (n >= 40 && n < 50) k = 40;
    if ((n - k) == 0) return 17497 - 160 * (k + 10);
    if ((n - k) == 1) return 47900;
    if ((n - k) == 2) return 114884;
    if ((n - k) == 3) return -90;
    if ((n - k) == 4) return 0;
    else return 0;//установка соперников в гараж, когда они не активны
}
gameform::gameform(gameplay *g, QQuickView *gar , QWidget *sh)
{
    Init();//инициализтровать
    shop = sh; game = g; garage = gar;
    left = false; right = false; forward = false; backward = false;
    hiper = false; up = false; shot = false; down = false;//управление изначально не активно
    game->space->speed=0;//скорость корабля 0
    game->space->sx=game->place[0].x;
    game->x=game->place[0].x/100;
    game->space->sy=game->place[0].y;
    game->y=game->place[0].y/100;
    game->space->sz=game->place[0].z;
    game->z=game->place[0].z/100;
    game->space->angle=-90;
    game->space->angle1=0;//установка корабля в гараж
    flewout=false;//корабль в гараже
    wait=false;//ожидание перед гонкой
}
gameform::~gameform()
{

}
void gameform::Init()
{
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QUrl::fromLocalFile("Gameform.qml"));
    this->rootContext()->setContextProperty("window1", this);
}//инициализация Qml скрипта
void gameform::keyPressEvent(QKeyEvent *event)
{
    if ((event->key()==Qt::Key_Left || event->key()==0x41 || event->key()==0x424) && !wait)
    {
        left=true;
        right=false;
    }
    if ((event->key()==Qt::Key_Right || event->key()==0x44 || event->key()==0x412) && !wait)
    {
        left=false;
        right=true;
    }
    if ((event->key()==0x57 || event->key()==0x426) && !wait)
    {
        forward=true;
        backward=false;
    }
    if ((event->key()==0x53 || event->key()==0x42B) && !wait)
    {
        backward=true;
        forward=false;
    }
    if ((event->key()==0x20) && !wait)
    {
        if (game->space->armlaser==100 && !game->part_in_single) shot=true;
        shooting(1);        
    }
    if ((event->key()==Qt::Key_R) && !wait) shooting(2);
    if ((event->key()==Qt::Key_H) && !wait) hiperjump();
    if ((event->key()==Qt::Key_Down || event->key()==Qt::Key_Q || event->key()==1049) && !wait)
    {
        up=false;
        down=true;
    }
    if ((event->key()==Qt::Key_Up || event->key()==Qt::Key_E || event->key()==1059) && !wait)
    {
        down=false;
        up=true;
    }
    if ((event->key()==90 || event->key()==1071) && !wait) rotate=1;
    if ((event->key()==88 || event->key()==1063) && !wait) rotate=2;
    if ((event->key()==Qt::Key_N ) && !wait) game->space->angle1=0;
    if (event->key()==1048 || event->key()==0x42) shop=new comp(this,game,true);
    if ((event->key()==Qt::Key_L || event->key()==1044) && !wait) shooting(2);
    if (event->key()==Qt::Key_Escape) pause1();
    if (event->key()==Qt::Key_P) game->space->activeshield=true;
    //инициализация кнопок управления с учетом русской раскладки

}
void gameform::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left || event->key()==0x41 || event->key()==0x424)
    {
        left=false;
        right=false;
    }
    if (event->key()==Qt::Key_Right || event->key()==0x44 || event->key()==0x412)
    {
        left=false;
        right=false;
    }
    if (event->key()==0x57 || event->key()==0x426)
    {
        forward=false;
        backward=false;
    }
    if (event->key()==0x53 || event->key()==0x42B)
    {
        backward=false;
        forward=false;
    }
    if (event->key()==Qt::Key_Down || event->key()==Qt::Key_Q || event->key()==1049)
    {
        up=false;
        down=false;
    }
    if (event->key()==Qt::Key_Up || event->key()==Qt::Key_E || event->key()==1059)
    {
        down=false;
        up=false;
    }
    if (event->key()==90 || event->key()==1071) rotate=0;
    if (event->key()==88 || event->key()==1063) rotate=0;
    if (event->key()==0x43 || event->key()==0x421) game->space->change_camera();
    //инициализация кнопок управления с учетом русской раскладки
}
void gameform::hiperjump()
{

}//гиперпрыжок
void gameform::shooting(int n)
{
    if (!game->part_in_single) game->player_shot(n);
}//выстрел
int gameform::get_data(int a)
{
    switch (a) {
    case 0:return game->space->sx;
    case 1:return game->space->sy;
    case 2:return game->space->sz;
    case 3:return game->space->speed;
    case 4:return game->space->anglesc;
    case 5:return game->space->health;
    case 6:return game->space->armlaser;
    case 7:return game->space->shield;
    case 8:return game->space->buttery_charge;
    case 10:return game->space->canonangle;
    case 11: return game->space->laserweapon;
    case 12: return game->space->tip;
    case 13:
    {
        if (shot) return 1;
        else return 0;
    }
    case 15: return game->space->rockets;
    case 16: return game->space->angle;
    case 17:
    {
        float k;
        if (game->space->camera==0 || game->space->camera==-180) k=((6+game->space->speed/3000)*cos(6.28*(game->space->angle-game->space->anglesc+game->space->camera)/360))*cos(6.28*(game->space->angle1+15*cos(6.28*game->space->camera/360))/360);
        else k=((6+game->space->speed/3000)*cos(6.28*(game->space->angle-game->space->anglesc+game->space->camera)/360));
        return k*100;
    }
    case 18:
    {
        float k;
        if (game->space->camera==0 || game->space->camera==-180) k=-((6+game->space->speed/3000)*sin(6.28*(game->space->angle-game->space->anglesc+game->space->camera)/360))*cos(6.28*(game->space->angle1+15*cos(6.28*game->space->camera/360))/360);
        else k=-((6+game->space->speed/3000)*sin(6.28*(game->space->angle-game->space->anglesc+game->space->camera)/360));
        return k*100;
    }
    case 19:
    {
        if (game->space->upgrades[2]) return 1;
        else return 0;
    }
    case 20:return game->space->angle1;
    case 21:
    {
        float k, mod;
        mod=2*sin(6.28*game->space->camera/360);
        if (mod<0) mod=-mod;
        k=((6+game->space->speed/3000)*sin(6.28*(game->space->angle1+15*cos(6.28*game->space->camera/360))/360))*cos(6.28*game->space->camera/360)+mod;
        return k*100;
    }
    case 22:return game->race->checked;
    case 23:return game->race->lap;
    case 24:return game->race->alllaps;
    case 25:return game->count;
    case 26:return game->space->rockshot;
    case 27:
    {
        if (flewout) return 1;
        else return 0;
    }
    case 28:return game->get_ship_params(0);
    case 29:return game->get_ship_params(1);
    case 30:return game->get_ship_params(2);
    case 31:return game->get_ship_params(3);
    case 32:return game->get_ship_params(4);
    case 33:return game->get_ship_params(5);
    case 34:return game->race->ringsize;
    case 35:
    {
        if (game->space->activeshield) return 1;
        else return 0;
    }

        default:
    {
        return (0);
            break;
        }
    }
}//выдача параметров на запросы Qml скрипта
void gameform::timerEvent(QTimerEvent *event)
{

    if (event->timerId()==Timer)
    {
        game->space->charging();
        game->space->driving(forward, backward, up, down, left, right);

        game->checking();
        game->timer1();

    int x,y,z;
    if (game->count==0) wait=false;
    else
    {
        game->count-=1;
        wait=true;
    }
    x=game->space->sx-game->place[0].x;
    y=game->space->sy-game->place[0].y;
    z=game->space->sz-game->place[0].z;
    if (sqrt(x*x+y*y+z*z)>3000) flewout=true;
    if (flewout && sqrt(x*x+y*y+z*z)<300 && !game->started) home();
    if (game->race!=NULL)
    {
        if (game->race->opponent[0]!=NULL && !wait)
        {
            game->opponent_driving();
        }
    }
    if (game->space->laseshot && game->space->armlaser>10) game->space->laseshot=false;
    if (game->finished)
    {
        pause=new Form(this,game,2);
        pause->showFullScreen();
        this->hide();
    }
    }
}//работа таймера
void gameform::showEvent(QShowEvent *)
{
    Timer=startTimer(40);//таймер 25 кадров в секунду
}
void gameform::hideEvent(QHideEvent *)
{
    killTimer(Timer);
}//при сворачивании ставим на паузу
void gameform::shot1()
{
    shot=false;
}//выстрел получение подтверждения от Qml
QString gameform::panel_output(int a)
{
    switch (a){
        case 0:
    {
       return QString::number(game->space->sx);
    }
    case 1:
    {
        QString output="Место "+QString::number(game->race->position)+"из "+QString::number(game->race->opp+1)+" \n Контрольная точка "+QString::number(game->race->checked)+"из 19 \n Круг"+QString::number(game->race->lap)+" из "+QString::number(game->race->alllaps)+"\n ";
        return output;
    }
    case 2: return game->get_ship_model(0);
    case 3: return game->get_ship_model(1);
    default:
    {
        return QString::number(game->space->speed);
    }
    }
}//Выдача данных панели
bool gameform::trackload()
{
    return game->trackloaded;
}//Команда загрузки трассы в Qml
int gameform::getcp(int x)
{
    return x;
}
void gameform::finishload()
{
    game->loadfinish();
}//подтверждение о загрузке трассы в сцену Qml
int gameform::get_point(int n)
{
    if (game->race==NULL) return 1;
    if (n<30) return game->race->checks[n]->x;
    if (n>=30 && n<60) return game->race->checks[n-30]->y;
    if (n>=60 && n<90) return game->race->checks[n-60]->z;
    if (n>=90 && n<120) return game->race->checks[n-90]->angle;
    if (n==121) return game->race->checked;
    else return 1;
}//Выдача координат контрольных точек
bool gameform::start()
{
    return game->started;
}//идет ли гонка, сообщение в Qml
void gameform::home()
{
    garage->showFullScreen();
    this->close();
}//Возвращение в гараж
int gameform::get_op_data(int n)
{
    if (game->race!=NULL)
    {
        if (n<10)
        {
            if (game->race->opponent[0]!=NULL) return game->race->opponent[0]->get_params(n);
            else return put_in_garage(n);
        }
        if (n>=10 && n<20)
        {
            if (game->race->opponent[1]!=NULL) return game->race->opponent[1]->get_params(n-10);
            else return put_in_garage(n);
        }
        if (n>=20 && n<30)
        {
            if (game->race->opponent[2]!=NULL) return game->race->opponent[2]->get_params(n-20);
            else return put_in_garage(n);
        }
        if (n>=30 && n<40)
        {
            if (game->race->opponent[3]!=NULL) return game->race->opponent[3]->get_params(n-30);
            else return put_in_garage(n);
        }
        if (n>=40 && n<50)
        {
            if (game->race->opponent[4]!=NULL) return game->race->opponent[4]->get_params(n-40);
            else return put_in_garage(n);
        }

        return 0;
    }    
    else return put_in_garage(n);
}//Выдача в qml данных о местонахождении соперников
void gameform::rocket()
{
    if (game->space->rockshot==11) game->space->rockshot=2;
    if (game->space->rockshot==12) game->space->rockshot=1;
}//выстрелы ракетами отображение в сцене
void gameform::finish()
{
    game->finished=false;
}//обработка финиширования
bool gameform::finished(){return game->finished;}
void gameform::pause1()
{
    pause=new Form(this,game,1);
    pause->showFullScreen();
    this->hide();
}//постановка игры на паузу
void gameform::radaring()
{
    if (game->space->upgrades[5] && game->race != NULL)//если есть радар и идет гонка
    {
        int i, disx, disy, disz;
        float distance1, distance2, a1, a2;
        int a11=game->space->angle, a12=game->space->angle1;
        disx = (game->space->sx/100)-game->race->checks[game->race->checked]->x;
        disy = (game->space->sy/100)-game->race->checks[game->race->checked]->y;
        disz = (game->space->sz/100)-game->race->checks[game->race->checked]->z;
        //определяем расстояние от игрока до цели по осям
        distance1 = sqrt((disx * disx)+(disy * disy));
        distance2 = sqrt((disz * disz)+(disy * disy));
        //и в горизонтальной/вертикальной плоскостях
        if (disy < 0) a1=360*acos(disx/distance1)/6.28;
        else a1 = -360*acos(disx/distance1)/6.28;
        a2=360*asin(disz/distance2)/6.28;
        distance1 = distance1 / 80;
        if (distance1 > 50) distance1 = 50;
        if (distance1 < -50) distance1 = -50;
        distance2 = distance2 / 80;
        if (distance2 > 50) distance2 = 50;
        if (distance2 < -50) distance2 = -50;//определяем положение точки на радаре
        aims[0][0]=distance1*cos(6.28*(a1-a11)/360);
        aims[0][1]=distance1*sin(6.28*(a1-a11)/360);
        aims[0][2]=distance2*sin(6.28*(-a2+a12)/360);//и передаем в скрипт
        i=1;
        while (i<game->race->opp)
        {
            disx=(game->space->sx/100)-game->race->opponent[i]->sx/100;
            disy=(game->space->sy/100)-game->race->opponent[i]->sy/100;
            disz=(game->space->sz/100)-game->race->opponent[i]->sz/100;
            distance1=sqrt((disx*disx)+(disy*disy));
            distance2=sqrt((disz*disz)+(disy*disy));
            if (disy<0) a1=360*acos(disx/distance1)/6.28;
            else a1=-360*acos(disx/distance1)/6.28;
            a2=360*asin(disz/distance2)/6.28;
            distance1=distance1/80;
            if (distance1>50) distance1=50;
            if (distance1<-50) distance1=-50;
            distance2=distance2/80;
            if (distance2>50) distance2=50;
            if (distance2<-50) distance2=-50;
            aims[i][0]=distance1*cos(6.28*(a1-a11)/360);
            aims[i][1]=distance1*sin(6.28*(a1-a11)/360);
            aims[i][2]=distance2*sin(6.28*(-a2+a12)/360);
            i++;
        }//соперников отслеживаем аналогично
        while (i < 25)
        {
            aims[i][0]=0;
            aims[i][1]=0;
            aims[i][2]=0;
            i++;
        }//заполняем нулями остальные слоты в массиве aims

    }
}//радар выдача параметров следующей контрольной точки и соперников
int gameform::get_radar(int n, int coord)
{
    int x = 0;
    x = aims[n][coord];
    if (x > 50) x = 50;
    if (x < -50) x = -50;
    return x;
}//выдача данных радара в qml скрипт
bool gameform::rad()
{
    return game->space->upgrades[5];
}//запрос Qml скрипта о наличии у игрока радара
