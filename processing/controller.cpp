#include "controller.h"


Controller::Controller(MainWindow * window, QObject *parent) : QObject(parent), m_window(window)
{
    m_player = new Player();
}

void Controller::createConnection()
{

}

void Controller::startApplication()
{
    m_window.show();
}

void Controller::controlOnClickedLoad()
{
    // Se baser sur ce qu'il y a dans MainWindow dans  le CodingExodus
}

void Controller::controlOnClickedPlay()
{

}

void Controller::controlOnClickedPause()
{

}

void Controller::controlOnProcessedImage()
{

}
