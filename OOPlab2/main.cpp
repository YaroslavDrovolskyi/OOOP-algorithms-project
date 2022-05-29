#include "mainwindow.h"
#include "mainmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  MainWindow w;
  //  w.show();
    MainMenu mm;
    mm.show();
    return a.exec();
}
