#include "mainwindow.h"
#include "simulatearea.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Основная программа
    SimulateArea area;
    area.show();

//    Будем использовать для теста
//    MainWindow w;
//    w.show();
    return a.exec();
}
