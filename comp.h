#ifndef COMP_H
#define COMP_H
#include <gameplay.h>
#include <QWidget>
#include <startform.h>

namespace Ui {
class comp;
}

class comp : public QWidget
{
    Q_OBJECT
private:
    int n, choosenrace;//выбранный трек
    bool shsh, board;//
    QWidget *set;
    QString race_information[10];//информация о гонках
    QQuickView *gar;//указатель на предыдущую форму
    bool k;
    gameplay *game1;//указатель на ядро игры
public:
    explicit comp(QQuickView *back, gameplay *game, bool board1, QWidget *parent = 0);
    ~comp();
    //void keyPressEvent(QKeyEvent *event);
protected:
    void keyReleaseEvent(QKeyEvent *event);
    void showitem(int number);//показать товар
  protected slots:
  void buy();
  void shop_go();//открыть магазин апгрейдов
  void salon_go();//открыть салон кораблей
  void desktop_go();//вернуться на рабочий стол
  void race_go();//меню выбора гонок
  void race1();//
  void race4();//
  void time1();//заезд на время
  void switchoff();//выключение
  void shopship();//переключение режимов магазина
  void buy_rockets();//заказ боеприпасов
  void repair();//вызов ремонтника
  void ladrace();//загрузить трек
  void tournamentshow();//показ информации о турнире
  void loadtournament(short int n);//загрузить турнир
private:
    Ui::comp *ui;
};

#endif // COMP_H
