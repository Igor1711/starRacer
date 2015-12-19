#include "comp.h"
#include "ui_comp.h"

comp::comp(QQuickView *back, gameplay *game, bool board1, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comp)
{
    ui->setupUi(this);
    gar=back;
    n=0;
    choosenrace = 0;//гонки не выбраны
    board=board1;
    game1=game;
    this->showFullScreen();
    QPalette Q=this->palette();
    QBrush br(Qt::TexturePattern);
    QImage monster1("image/space2.jpg");
    br.setTextureImage(monster1.scaled(1366,768));
    Q.setBrush(QPalette::Background,br);
    this->setPalette(Q);//установка фоновой картинки
    race_information[0]="Один заезд по выбранной трассе с соперниками без оружия.\n Победитель получает денежный приз. Возможно прохождение трассы на время без соперников";
    race_information[1]="Заезд новичков \n Кругов: 1, Соперников: 2, \n Приз: $5000";
    race_information[2]="Любительская гонка \n Кругов: 2, Соперников: 4, \n Приз: $8000";
    race_information[3]="Для опытных \n Кругов: 3, Соперников: 4, \n Призы: 1-й $10000, 2-й $5000, 3-й $1500";
    race_information[4]="Заезд профессионалов \n Кругов: 5, Соперников: 5, \n Призы: 1-й $25000, 2-й $15000, 3-й $8000";
    race_information[5]="Турнир представляет собой серию гонок c соперниками и оружием. Место игрока по итогам турнира определяется турнирной таблицей. \n После победы открывается следующий турнир";
    race_information[6]="Начало карьеры \n Две гонки по 3 круга с пятью соперниками. Уровень сложности - низкий. \n Награды: 1-й: 15000, 2-й: 10000, 3-й: 7000 \n Победа открывает турнир любителей";
    race_information[7]="Турнир любителей \n Три гонки по 3 круга с пятью соперниками. Уровень сложности - низкий. \n Награды: 1-й: 18000, 2-й: 11000, 3-й: 7000 \n Победа открывает профессиональную карьеру";
    race_information[8]="Начало карьеры \n Четыре гонки по 3 круга с пятью соперниками. Уровень сложности - средний. \n Награды: 1-й: 35000, 2-й: 27000, 3-й: 10000 \n Победа открывает лигу чемпионов";
    race_information[9]="Лига чемпионов \n Четрыре гонки по 4 круга с пятью соперниками. Уровень сложности - сложный. \n Награды: 1-й: 65000, 2-й: 30000, 3-й: 17000";
    ui->textBrowser_2->setText(race_information[0]);
    ui->textBrowser_5->setText(race_information[5]);
    ui->race1->setEnabled(false);
    ui->race4->setEnabled(false);
    ui->time1->setEnabled(false);
    connect(ui->pushButton_3,SIGNAL(clicked()),SLOT(salon_go()));
    connect(ui->pushButton_4,SIGNAL(clicked()),SLOT(shop_go()));
    connect(ui->pushButton_5,SIGNAL(clicked()),SLOT(race_go()));
    connect(ui->back, SIGNAL(clicked()),SLOT(desktop_go()));
    connect(ui->exit, SIGNAL(clicked()), SLOT(switchoff()));
    connect(ui->ships, SIGNAL(currentIndexChanged(int)), SLOT(shopship()));
    connect(ui->goods, SIGNAL(currentIndexChanged(int)), SLOT(shopship()));
    connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(buy()));
    connect(ui->racechoose, SIGNAL(currentIndexChanged(int)),SLOT(ladrace()));
    connect(ui->tournamentchoose, SIGNAL(currentIndexChanged(int)),SLOT(tournamentshow()));
    connect(ui->race1, SIGNAL(clicked()), SLOT(race1()));
    connect(ui->race4, SIGNAL(clicked()),SLOT(race4()));
    connect(ui->time1, SIGNAL(clicked()),SLOT(time1()));
    connect(ui->pushButton_6,SIGNAL(clicked()),SLOT(buy_rockets()));
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(repair()));//привязка процедур к кнопкам
    desktop_go();
    ui->money->setText("$"+QString::number(game1->money));
    if (board)
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_6->setVisible(true);
        if (game1->space->health<100) ui->pushButton->setVisible(true);
        else ui->pushButton->setVisible(false);
    }
    else
    {
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_6->setVisible(false);
        ui->pushButton->setVisible(false);
    }//в зависимотси от того, откуда вызвана форма дестктоп имеет набор кнопок стационарного компа или борткомпьютера
}

comp::~comp()
{
    set->show();
    delete ui;

}
void comp::desktop_go()//вернуться на рабочий стол
{
    ui->back->setVisible(false);
    ui->shops->setVisible(false);
    ui->race->setVisible(false);
    ui->desktop->setVisible(true);
    k=false;
}
void comp::shop_go()//открыть интернет-магазин
{
    ui->back->setVisible(true);
    ui->desktop->setVisible(false);
    ui->shops->setVisible(true);
    ui->ships->setVisible(false);
    ui->goods->setVisible(true);
    ui->label->setVisible(true);
    ui->label_2->setVisible(false);
    shsh=false;
    k=true;
    if (game1->space==NULL) ui->pushButton_7->setEnabled(false);//если нет корабля апгрейды недоступны, кнопка купить отключена
    else ui->pushButton_7->setEnabled(true);
    n=5;
    showitem(n);//показ товров
    if ((game1->good[n]->price)>(game1->money)) ui->pushButton_7->setEnabled(false);//кнопка купить активна только когда достаточно денег
}
void comp::salon_go()//переход в салон продажи кораблей
{
    ui->back->setVisible(true);
    ui->desktop->setVisible(false);
    ui->ships->setVisible(true);
    ui->shops->setVisible(true);
    ui->goods->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(true);
    shsh=true;
    k=true;
    n=0;
    ui->pushButton_7->setEnabled(true);
    showitem(n);
    if (game1->good[n]->price>game1->money) ui->pushButton_7->setEnabled(false);
}
void comp::race_go()//переход в установки гонок
{
    ui->back->setVisible(true);
    ui->desktop->setVisible(false);
    ui->race->setVisible(true);
    k=true;
    n=2;
}
void comp::race1()//загрузка одиночной гонки
{
    if (choosenrace==1) game1->loadtrack(0,1,2);
    if (choosenrace==2) game1->loadtrack(1,2,4);
    if (choosenrace==3) game1->loadtrack(2,3,4);
    if (choosenrace==4) game1->loadtrack(3,5,5);
    switchoff();
    game1->part_in_single=true;//загрузка трассы, выключение компа
}

void comp::race4()//загрузка турнира
{
    loadtournament(ui->tournamentchoose->currentIndex());
    switchoff();
}
void comp::time1()
{
    if (choosenrace==1) game1->loadtrack(0,1,0);
    if (choosenrace==2) game1->loadtrack(1,2,0);
    if (choosenrace==3) game1->loadtrack(2,3,0);
    if (choosenrace==4) game1->loadtrack(3,4,0);
    switchoff();//загрузка трассы, выключение компа
}


void comp::buy()
{
    if (shsh)//если мы в салоне кораблей
    {        
        if (game1->my_ship_num < 4) //Если не переполнен гараж
        {
            game1->space=new My_ship(n+1, game1->good[n]->price);
            game1->just_bought=true;//отображаем, что только что куплен корабль
            game1->my_garage[game1->my_ship_num] = game1->space;
            game1->choosen_ship = game1->my_ship_num;
            game1->my_ship_num++;//добавляем корабль в гараж
        }
    }
    else
    {
        if (game1->space!=NULL)//покупка апгрейдов
        {
            game1->space->upgrade(n-5,game1->good[n]->price);//улучшаем корабль
        }
        if (n == 13)//покупка робота
        {
            int i;
            for (i = 5; i < 13; i++) game1->good[i]->price -= 100;//уменьшение стоимости апгрейдов засчет своей установки
        }
    }
    game1->money-=game1->good[n]->price;//вычитаем цену покупки
    ui->money->setText("$"+QString::number(game1->money));//обновляем "баланс"
    game1->save_game();//сохраняем игру
    ui->pushButton_7->setEnabled(false);

}
void comp::switchoff()
{
    if (board==false) gar->showFullScreen();
    this->close();//выключение компа, врзвращение на форму, откуда он был включен
}
void comp::shopship()//Переключение товара в магазине
{
    if (shsh) n=ui->ships->currentIndex();
    else n=ui->goods->currentIndex()+5;
    ui->pushButton_7->setEnabled(true);
    if (game1->space==NULL && shsh==false) ui->pushButton_7->setEnabled(false);//Нет корабля, нечего апгрейдить
    if (shsh && game1->my_ship_num == 4) ui->pushButton_7->setEnabled(false);//Гараж полон
    if (game1->space!=NULL)
    {
        if (shsh==false && game1->space->upgrades[n-5]==true) ui->pushButton_7->setEnabled(false);
    }//блокируем кнопку купить, если недостаточно денег
    showitem(n);//отображаем выбранный товар
}

void comp::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Escape)
    {
        if (k) desktop_go();//выключение кнопкой эскейп
        else switchoff();
    }
}
void comp::showitem(int number)//показ товара
{
    QImage good;
    ui->price->setText("$"+QString::number(game1->good[number]->price));
    if ((game1->good[n]->price)>(game1->money)) ui->pushButton_7->setEnabled(false);
    QPalette Q1=this->ui->goodview->palette();
    QBrush br(Qt::TexturePattern);
    if (shsh) good=QImage("/home/igor/qt-projects/Space-Racers/image/ships/"+QString::number(number)+".jpg");
    else good=QImage("/home/igor/qt-projects/Space-Racers/image/goods/"+QString::number(number-5)+".jpg");
    br.setTextureImage(good.scaled(200,150));
    ui->goodview->setFixedSize(200,150);
    Q1.setBrush(QPalette::Background,br);
    this->ui->goodview->setPalette(Q1);
    //this->ui->textBrowser->set
    this->ui->textBrowser->setText((game1->good[number]->name)+"\n"+(game1->good[number]->use1));
}
void comp::buy_rockets()//покупка ракет
{
    game1->space->rockets+=10;//пополнение боекомплекта
    game1->money-=85;//оплата
}
void comp::repair()//
{
    game1->money-=((100-game1->space->health)*20);//оплата ремонта
    game1->space->health=100;//восстановление здоровья
    ui->pushButton->setVisible(false);
}
void comp::ladrace()//показ информации о гонке
{
    int x;
    x=ui->racechoose->currentIndex();
    ui->textBrowser_2->setText(race_information[x]);
    if (x==0)
    {
        ui->race1->setEnabled(false);
        ui->time1->setEnabled(false);
    }
    else
    {
        choosenrace=x;
        ui->race1->setEnabled(true);
        ui->time1->setEnabled(true);
    }
}
void comp::tournamentshow()//показ информации о турнире
{
    int x;
    x=ui->tournamentchoose->currentIndex();
    ui->textBrowser_5->setText(race_information[x+5]);
    if (x==0) ui->race4->setEnabled(false);
    else ui->race4->setEnabled(true);
}
void comp::loadtournament(short n)//загрузить турнир
{
    game1->tournament=n;//номер загружаемого турнира
    int i=0;
    while (i < 6)
    {
        game1->tournament_table[i]=0;//обнуляем турнирную таблицу
        i ++;
    }
    if (n == 1)
    {
        game1->rest_races = 2;
    }
    if (n == 2)
    {
        game1->rest_races = 3;
    }
    if (n == 3)
    {
        game1->rest_races = 4;
    }
    if (n == 4)
    {
        game1->rest_races = 4;//установка количества гонок
    }
    game1->tournament_start();//запускаем турнир
}
