#ifndef GARAGE_H
#define GARAGE_H

#include <QQuickView>
//#include <Qt3D>
#include <startform.h>
#include <gameplay.h>
#include <comp.h>
#include <gameform1.h>

namespace Ui {
class Garage;
}

class Garage : public QQuickView
{
    Q_OBJECT
    
private:
    QWidget *computer, *start;//формы компьютер и стартовая
    gameplay *game;//указатель на ядро
    QQuickView *city;//основная игровая форма
    void Init();//инициализация
    void keyReleaseEvent(QKeyEvent *event);//обработка кнопок
public:
    explicit Garage(QWidget *s, gameplay *g);
    ~Garage();

private slots:


public slots:
    void fly_out();//вылет
    void switchcomp_on();//включение компа
    QString give_info(int param);//выдача информации
    int ret();//
    bool deliver_ship();//доставка корабля
    QString get_ship_model(short n);//запрос путей к 3д моделям
    int get_ship_params(short n);//запрос параметров
    bool change_ship();//смена корабля
private:
    QQuickView *ui;
};

#endif // GARAGE_H
