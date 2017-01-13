#include "views/mainwindow.h"
#include <QApplication>
<<<<<<< HEAD
#include "controller.h"
#include "projectmodel.h"
=======
#include "models/projectmodel.h"
#include <QDebug>
>>>>>>> 94a60ea9078b52163661f1438c0ae46ffa6cb64d

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    Controller controller(&window,);

    return a.exec();
}
