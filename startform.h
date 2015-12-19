#ifndef STARTFORM_H
#define STARTFORM_H

#include "gameplay.h"
#include <QWidget>
#include <QQuickView>
#include <garage.h>

namespace Ui {
class startform;
}

class startform : public QWidget
{
    Q_OBJECT
    int k;
    QQuickView *garage;
    QWidget *computer;
    gameplay *game;

public:
    explicit startform(QWidget *parent = 0);
    ~startform();
    void keyReleaseEvent(QKeyEvent *event);
private slots:
    void exit_game();
    void ex_prove();
    void ex_abolish();
    void new_game();
    void load_game();
    void showEvent();
private:
    Ui::startform *ui;
    void play();
};

#endif // STARTFORM_H
