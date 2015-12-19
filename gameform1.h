#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>
#include <QQuickView>
#include <Qt3D>
#include "gameplay.h"
#include "comp.h"
#include "form.h"
#include <QPainter>

namespace Ui {
class gameform;
}

class gameform : public QQuickView
{
    Q_OBJECT
  private:
    QWidget *shop, *pause;
    QQuickView *garage;
    gameplay *game;
    bool left, forward, right, backward, hiper, up, down,shot, wait;
    int Timer, rotate, flewout;
    int aims[25][3];

public:
    explicit gameform(gameplay *g, QQuickView *gar, QWidget *sh);
    ~gameform();
protected:
    void Init();
    void running();
    void shooting(int n);
    void hiperjump();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void showEvent(QShowEvent *);
    void pause1();
    void hideEvent(QHideEvent *);

public slots:
    int get_data(int a);
    void shot1();
    QString panel_output(int a);
    int getcp(int x);
    bool trackload();
    bool start();
    void finishload();
    int get_point(int n);
    void home();
    void rocket();
    int get_op_data(int n);
    void finish();
    bool finished();
    int get_radar(int n, int coord);
    bool rad();
    void radaring();
private:

};

#endif // GAMEFORM_H
