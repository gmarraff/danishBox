#include "welcomeform.h"
#include "loginform.h"
#include <QApplication>
#include "box.h"
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeForm w;
    w.show();

    return a.exec();
}
