#include "views/mainwindow.h"
#include <QApplication>
#include "models/projectmodel.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
