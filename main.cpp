#include "mysprite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySprite w;
    w.show();

    return a.exec();
}
