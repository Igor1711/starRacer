#ifndef GAMEFORM_H
#define GAMEFORM_H
#include <gameplay.h>
#include <QQuickView>
#include <QWidget>

//#include <panda3d/windowFramework.h>

class gameform1
{
    gameplay *game;
    QQuickView *garage;
    QWidget *pause;

public:
    gameform(gameplay *g, QQuickView *back);
    void show();
};

#endif // GAMEFORM_H
