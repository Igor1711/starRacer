#include "form.h"
#include "ui_form.h"

Form::Form(QQuickView *b, gameplay *p, int fin,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    base=b;
    game=p;
    call=fin;
    this->showFullScreen();
    QPalette Q=this->palette();
    QBrush br(Qt::TexturePattern);
    QImage monster1("/home/igor/qt-projects/Space-Racers/image/race-pause.jpg");
    br.setTextureImage(monster1.scaled(1366,768));
    Q.setBrush(QPalette::Background,br);
    this->setPalette(Q);//установка картинки
    connect(ui->go_on, SIGNAL(clicked()),SLOT(back1()));
    connect(ui->restart, SIGNAL(clicked()),SLOT(restart()));
    connect(ui->return_2, SIGNAL(clicked()),SLOT(return_to_garage()));
    connect(ui->yes, SIGNAL(clicked()),SLOT(agree()));
    connect(ui->no, SIGNAL(clicked()),SLOT(refuse()));
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(back()));//привязка кнопок
    ui->money->setText("$"+QString::number(game->money));//отображение баланса
    if (game->started) ui->restart->setVisible(true);//если идет гонка, отображаем кнопку рестарт
    else ui->restart->setVisible(false);//иначе прячем
    state=0;
    ui->tableview->setVisible(false);
    if (fin == 1)//если вызвана пауза
    {
        ui->question->setVisible(false);
        ui->finisher->setVisible(false);
        ui->pause_2->setVisible(true);
    }
    else //если это конец гонки
    {
        ui->question->setVisible(false);
        ui->finisher->setVisible(true);
        ui->pause_2->setVisible(false);
        if (game->race->position==1) ui->label_2->setText("Поздравляем Вас с победой");//поздравление победителю
        else ui->label_2->setText("Вы заняли "+QString::number(game->race->position)+" место");//какое место занял игрок
        if (game->tournament != 0)//если идет турнир
        {
            ui->tableview->setVisible(true);//показываем турнирную таблицу
            QString table1="Player               "+QString::number(game->tournament_table[0])+"\n";
            int i=1;
            while (i<6)
            {
                table1+="Opponent"+QString::number(i)+"             "+QString::number(game->tournament_table[i])+"\n";
                i++;
            }
            ui->tableview->setText(table1);
        }
        if (game->race->position<4 && game->race->opp!=0 && game->tournament==0)
        {
            ui->priseview->setFixedWidth(this->width());
            QPalette Q=this->ui->priseview->palette();
            QBrush br(Qt::TexturePattern);
            QImage cuboc("/home/igor/qt-projects/Space-Racers/image/prise"+QString::number(game->race->position)+".jpg");
            br.setTextureImage(cuboc.scaled(ui->priseview->width(),this->height()*0.5));
            Q.setBrush(QPalette::Background,br);
            this->ui->priseview->setPalette(Q);
            ui->priseview->setVisible(true);
        }
        else ui->priseview->setVisible(false);
        ui->result->setText("Ваш результат составляет: "+QString::number(game->min)+":"+QString::number(game->sec)+":"+QString::number(game->mil));
        if (game->race->opp==0) ui->label_2->setVisible(false);
        else ui->label_2->setVisible(true);
        game->race=NULL;
    }
}

Form::~Form()
{
    delete ui;
}
void Form::back()
{
    if (game->tournament > 0)//если идет турнир
    {
        if (game->rest_races > 0)//если текущая гонка не последняя
        {
            game->tournament_continue();//продолжение турнира
            base->showFullScreen();//игровую форму в полноэкранный режим
            this->close();//текущую - закрыть
        }
        else//если завершена последняя гонка
        {
            short int k = game->tournament;//номер турнира
            ui->label_2->setText("Вы заняли "+QString::number(game->tournament_finish())+" место");
            //вывод какое место занял игрок
            if (game->tournament_finish() < 4)//если игрок занял призовое место
            {
                ui->priseview->setFixedWidth(this->width());
                QPalette Q=this->ui->priseview->palette();
                QBrush br(Qt::TexturePattern);
                QImage cuboc1("/home/igor/qt-projects/Space-Racers/image/prise"+QString::number(game->tournament_finish())+".jpg");
                //вывдоим изображение кубка, если занято призовое место
                br.setTextureImage(cuboc1.scaled(ui->priseview->width(),this->height()*0.5));
                Q.setBrush(QPalette::Background,br);
                this->ui->priseview->setPalette(Q);
                ui->priseview->setVisible(true);//показ кубка
                ui->tableview->setVisible(false);//убираем таблицу
                if (k==1)
                {
                    if (game->tournament_finish()==1) game->money+=15000;
                    if (game->tournament_finish()==2) game->money+=10000;
                    if (game->tournament_finish()==3) game->money+=7000;
                }
                if (k==2)
                {
                    if (game->tournament_finish()==1) game->money+=18000;
                    if (game->tournament_finish()==2) game->money+=11000;
                    if (game->tournament_finish()==3) game->money+=7000;
                }
                if (k==3)
                {
                    if (game->tournament_finish()==1) game->money+=35000;
                    if (game->tournament_finish()==2) game->money+=27000;
                    if (game->tournament_finish()==3) game->money+=10000;
                }
                if (k==4)
                {
                    if (game->tournament_finish()==1) game->money+=65000;
                    if (game->tournament_finish()==2) game->money+=30000;
                    if (game->tournament_finish()==3) game->money+=17000;
                }//денежный приз за занятие призового места
            }
        }
    }
    else
    {
        base->showFullScreen();
        this->close();
    }
    game->save_game();
}
void Form::restart()
{
    ui->label->setText("Вы действительно хотите начать гонку заново?");
    state=1;
    ui->pause_2->setVisible(false);
    ui->question->setVisible(true);
}
void Form::return_to_garage()
{
    if (game->started) ui->label->setText("Вы действительно хотите покинуть гонку?");
    else ui->label->setText("Вы действительно хотите вернуться в гараж?");
    ui->pause_2->setVisible(false);
    ui->question->setVisible(true);
    state=2;
}
void Form::agree()//игрок согласился
{
    if (state == 2)//возвращение в гараж
    {
        game->space->sx=game->place[0].x;
        game->space->sy=game->place[0].y;
        game->space->sz=game->place[0].z;
        game->x=game->place[0].x / 100;
        game->y=game->place[0].y / 100;
        game->z=game->place[0].z / 100;//возвращаем корабль в гараж
        game->started=false;//если шла гонка, то сходим с дистанции
        game->space->speed = 0;//скорость 0
        game->space->angle = -90;
        game->space->angle1 = 0;

    }
    if (state == 1)//рестарт гонки
    {
        int i = 0;
        game->space->sx=game->place[2].x + 600 * cos(3.14 * game->race->opp);
        game->space->sz=game->place[2].z;
        game->space->sy=game->place[2].y-600 * game->race->opp;
        game->x=game->place[1].x / 100;
        game->y=game->place[1].y / 100;
        game->z=game->place[1].z / 100;
        game->space->angle = 90;
        game->space->angle1 = 0;
        game->space->speed = 0;//возвращаем игрока на старт и останавливаем
        game->race->lap = 1;//обнуляем круги
        game->race->checked = 0;//обнуляем счетчик контрольных точек
        while  (i<game->race->opp)
        {
            game->race->opponent[i]->sx=game->place[2].x + 600 * cos(3.14 * i);
            game->race->opponent[i]->sy=game->place[2].y - 600 * i;
            game->race->opponent[i]->sz=game->place[2].z;
            game->race->opponent[i]->angle=90;
            game->race->opponent[i]->angle1=0;
            game->race->opponent[i]->points=0;
            game->race->opponent[i]->speed=0;
            game->race->opponent[i]->lap=1;
            i++;//возвращаем соперников на старт
        }
        game->count=60;//таймер обратного отсчета перед гонкой
    }
    back1();
}
void Form::refuse()//игрок отказался, возвращаемся на игровую форму
{
    ui->pause_2->setVisible(true);
    ui->question->setVisible(false);
    state=0;
}
void Form::closeEvent(QCloseEvent *)
{

}
void Form::back1()//возврат в игру
{
    base->showFullScreen();
    this->close();
}
