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
    connect(&m_window,SIGNAL(viewClickedPlay()),this,SLOT(controlOnClickedPlay()));
    connect(this,SIGNAL(controlChangeButtonPlay(bool)),&m_window,SLOT(viewOnChangeButtonPlay(bool)));
    connect(m_player, SIGNAL(processedImage(QImage)),this, SLOT(controlOnUpdatePlayer(QImage)));
    connect(this,SIGNAL(controlUpdatePlayer(QImage,double)),&m_window,SLOT(viewOnUpdatePlayer(QImage,double)));
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
    bool play = true;
    if (m_player->isStopped())
    {
        m_player->Play();
        play = false;
    }else
    {
        m_player->Stop();
    }
    emit controlChangeButtonPlay(play);
}

void Controller::controlOnClickedPause()
{

}

void Controller::controlOnProcessedImage()
{

}

void Controller::controlOnUpdatePlayer(QImage img)
{
    if (!img.isNull())
        {
            emit controlUpdatePlayer(img,m_player->getCurrentFrame());
        }
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
