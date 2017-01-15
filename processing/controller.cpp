#include "controller.h"


Controller::Controller(MainWindow * window, QObject *parent) : QObject(parent), m_window(window)
{
    m_player = new Player();
    createConnection();
}

void Controller::createConnection()
{
    connect(&m_window,SIGNAL(viewClickedLoad()),this,SLOT(controlOnClickedLoad()));
    connect(this,SIGNAL(controlOpenLoadVideo()),&m_window,SLOT(viewOnLoadVideo()));
    connect(&m_window,SIGNAL(viewGetNameVideoLoad(QString)),this , SLOT(controlOnGetNameVideo(QString)));
    connect(this,SIGNAL(controlErrorLoad()),&m_window,SLOT(viewOnErrorLoad()));
    connect(this,SIGNAL(controlSuccededLoad(QString,double,double)),&m_window,SLOT(viewOnSuccededLoad(QString,double,double)));
}

void Controller::startApplication()
{
    m_window.show();
}

void Controller::controlOnClickedLoad()
{
    emit controlOpenLoadVideo();
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

void Controller::controlOnGetNameVideo(QString filename)
{
    if (!filename.isEmpty()){
            if (!m_player->loadVideo(filename.toAscii().data()))
            {
                emit controlErrorLoad();
            }
            else{
                emit controlSuccededLoad(filename,m_player->getNumberOfFrames(),m_player->getFrameRate());
            }
        }
}
