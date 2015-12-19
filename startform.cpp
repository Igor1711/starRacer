#include "startform.h"
#include "ui_startform.h"

startform::startform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startform)
{
    ui->setupUi(this);
    this->ui->yesbutton->setVisible(false);
    this->ui->nobutton->setVisible(false);
    this->ui->ask->setVisible(false);
    this->showFullScreen();//разворот в полноэкранный режим
    k=0;
    QPalette Q=this->palette();
    QBrush br(Qt::TexturePattern);
    QImage monster1("./image/space3.jpg");
    br.setTextureImage(monster1.scaled(1366,768));
    Q.setBrush(QPalette::Background,br);
    this->setPalette(Q);//установка фоновой картинки
    connect(ui->playbutton,SIGNAL(clicked()),SLOT(load_game()));
    connect(ui->yesbutton,SIGNAL(clicked()),SLOT(ex_prove()));
    connect(ui->exit1,SIGNAL(clicked()),SLOT(exit_game()));
    connect(ui->nobutton,SIGNAL(clicked()),SLOT(ex_abolish()));
    connect(ui->newgame, SIGNAL(clicked()), SLOT(new_game()));//связь кнопок и процедур

}

startform::~startform()
{
    delete ui;
}
void startform::exit_game()//выход из игры
{
    this->ui->yesbutton->setVisible(true);
    this->ui->nobutton->setVisible(true);
    this->ui->ask->setVisible(true);
    this->ui->playbutton->setVisible(false);
    this->ui->newgame->setVisible(false);
    this->ui->exit1->setVisible(false);
    ui->yesbutton->setFocus();//выводим вопрос и кнопки да/нет, остальные кнопки убираем
    k=1;
}
void startform::ex_prove()//подтверждение выхода из игры
{
    this->close();
    exit(0);//если игрок ответил да, выходил из игры
}
void startform::ex_abolish()//игрок отказался выходить
{
    this->ui->yesbutton->setVisible(false);
    this->ui->nobutton->setVisible(false);
    this->ui->ask->setVisible(false);
    this->ui->playbutton->setVisible(true);
    this->ui->newgame->setVisible(true);
    this->ui->exit1->setVisible(true);//возвращаем форму в изначальный вид
    k=0;
}
void startform::play()//кнопка гараж, начинаем новую игру.
{
    garage=new Garage(this, game);
    garage->showFullScreen();
    this->hide();//переходим в гараж
}

void startform::showEvent()
{
    this->showFullScreen();//разворот в полный экран при активации формы.
}

void startform::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Escape)
    {
        if (k==0) exit_game();
        else ex_abolish();//обработка кнопок, выход по эскейп
    }
}

void startform::new_game()//Новая игра
{
    game=new gameplay(false);
    play();
}
void startform::load_game()//Загрузитьсохраненную игру
{
    game=new gameplay(true);
    play();
}
