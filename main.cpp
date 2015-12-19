#include "startform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startform w;
    w.show();

    return a.exec();
}
