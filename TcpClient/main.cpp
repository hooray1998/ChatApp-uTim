#include "widget.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    bool test = false;
    if(test)
    {
        srand(time(NULL));
        w.test();
        w.move(200*(rand()%4+1),80*(rand()%3+1));
    }
    else
        w.showLoginWidget();

    return a.exec();
}
