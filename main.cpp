#include "views/mainwindow.h"
#include <QApplication>
#include "controller.h"
#include "projectmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    Controller controller(&window,);

    return a.exec();
}
