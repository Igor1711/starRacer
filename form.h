#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QQuickView>
#include <gameplay.h>
#include "gameform1.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
private:
    QQuickView *base;//указатель на основную игровую форму
    gameplay *game;//указатель на ядро
    int state, call;
    void closeEvent(QCloseEvent *);
protected slots:
    void back();//назад
    void restart();//рестарт
    void return_to_garage();//вернуться в гараж
    void refuse();//отказ
    void agree();//согласие
    void back1();//назад
public:
    explicit Form(QQuickView *b, gameplay *p, int fin, QWidget *parent = 0);

    ~Form();
    
private:
    Ui::Form *ui;
};

#endif // FORM_H
