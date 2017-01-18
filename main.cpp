#include "views/mainwindow.h"
#include <QApplication>

#include "controllers/controller.h"
#include "models/projectmodel.h"
#include "processing/BackgroundDetector.h"
#include "processing/qtipl.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow window;
    Controller controller(&window);
    controller.startApplication();

    return a.exec();
}
