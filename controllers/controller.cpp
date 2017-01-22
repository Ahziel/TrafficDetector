#include "controllers/controller.h"
#include <iostream>


Controller::Controller(MainWindow * window, QObject *parent) : QObject(parent), m_window(window),m_playerState(false)
{
    m_player = new Player();
    m_trafficDetector = new TrafficDetector();
    createConnection();
}

Controller::~Controller()
{
    delete m_player;
    delete m_trafficDetector;
}

/*
 * Fonction pour initialiser les différentes connexions à la création
 *
 */
void Controller::createConnection()
{
    connect(&m_window,SIGNAL(viewClickedLoad()),this,SLOT(controlOnClickedLoad()));
    connect(this,SIGNAL(controlOpenLoadVideo()),&m_window,SLOT(viewOnLoadVideo()));
    connect(&m_window,SIGNAL(viewGetNameVideoLoad(QString)),this , SLOT(controlOnGetNameVideo(QString)));
    connect(this,SIGNAL(controlErrorLoad()),&m_window,SLOT(viewOnErrorLoad()));
    connect(this,SIGNAL(controlSuccededLoad(QString,double,QString)),&m_window,SLOT(viewOnSuccededLoad(QString,double,QString)));
    connect(&m_window,SIGNAL(viewClickedPlay()),this,SLOT(controlOnClickedPlay()));
    connect(this,SIGNAL(controlChangeButtonPlay(bool)),&m_window,SLOT(viewOnChangeButtonPlay(bool)));
    connect(m_player, SIGNAL(processedImage(QImage)),this, SLOT(controlOnUpdatePlayer(QImage)));
    connect(this,SIGNAL(controlUpdatePlayer(QImage,double,QString)),&m_window,SLOT(viewOnUpdatePlayer(QImage,double,QString)));
    connect(&m_window,SIGNAL(viewSliderPressed()),this,SLOT(controlOnSliderPressed()));
    connect(&m_window,SIGNAL(viewSliderReleased()),this,SLOT(controlOnSliderReleased()));
    connect(&m_window,SIGNAL(viewSliderMoved(int)),this,SLOT(controlOnSliderMoved(int)));
    connect(this,SIGNAL(controlFrameChange(QString)),&m_window,SLOT(viewOnFrameChange(QString)));
    connect(&m_window,SIGNAL(viewChangeFrameRate(QString)),this,SLOT(controlOnChangeFrameRate(QString)));
    connect(m_player, SIGNAL(processedImage(QImage)), m_trafficDetector, SLOT(receiveFrameToProcess(QImage)));
    connect(m_trafficDetector, SIGNAL(sendProcessedFrame(QImage*)), &m_window, SLOT(viewOnProcessedFrame(QImage*)));
    connect(&m_window,SIGNAL(viewClickedStop()), this, SLOT(controlOnClickedStop()));
    connect(this,SIGNAL(controlStopPlay()),&m_window,SLOT(viewOnStop()));
    connect(&m_window, SIGNAL(viewGammaChanged(double)), this, SLOT(controlOnGammaChanged(double)));
    connect(this, SIGNAL(controlGammaChanged(double)), m_trafficDetector, SLOT(receiveSetBackgroundDetectorGamma(double)));
    connect(&m_window, SIGNAL(viewThresholdChanged(int)), this, SLOT(controlOnThresholdChanged(int)));
    connect(this, SIGNAL(controlThresholdChanged(int)), m_trafficDetector, SLOT(receiveSetThreshold(int)));
    connect(&m_window, SIGNAL(viewDilationChanged(int)), this, SLOT(controlOnDilationChanged(int)));
    connect(this, SIGNAL(controlDilationChanged(int)), m_trafficDetector, SLOT(receiveSetDilation(int)));
    connect(&m_window, SIGNAL(viewErosionChanged(int)), this, SLOT(controlOnErosionChanged(int)));
    connect(this, SIGNAL(controlErosionChanged(int)), m_trafficDetector, SLOT(receiveSetErosion(int)));
    connect(&m_window, SIGNAL(viewOutputChanged(int)), this, SLOT(controlOnOutputChanged(int)));
    connect(this, SIGNAL(controlOutputChanged(int)), m_trafficDetector, SLOT(receiveOutputChange(int)));
    connect(m_trafficDetector, SIGNAL(countedVehicules(int)), this, SLOT(controlOnVehiculesCounted(int)));
    connect(this, SIGNAL(controlVehiculesCounted(int)), &m_window, SLOT(viewOnCountedVehicules(int)));
}

void Controller::startApplication()
{
    m_window.show();
}

QString Controller::getFormattedTime(int timeInSeconds)
{

        int seconds = (int) (timeInSeconds) % 60 ;
        int minutes = (int) ((timeInSeconds / 60) % 60);
        int hours   = (int) ((timeInSeconds / (60*60)) % 24);

        QTime t(hours, minutes, seconds);
        if (hours == 0 )
            return t.toString("mm:ss");
        else
            return t.toString("h:mm:ss");
}

void Controller::controlOnClickedLoad()
{
    emit controlOpenLoadVideo();
}

void Controller::controlOnClickedPlay()
{
    if (!m_playerState)
    {
        m_player->Play();
        m_playerState = !m_playerState;
    }else
    {
        m_player->Stop();
        m_playerState = !m_playerState;
    }
    emit controlChangeButtonPlay(!m_playerState);
}

void Controller::controlOnSliderPressed()
{
    m_player->Stop();
}

void Controller::controlOnSliderReleased()
{
    if(m_playerState)
    {
       m_player->Play();
    }
}

void Controller::controlOnSliderMoved(int current)
{
    m_player->setCurrentFrame(current);
    emit controlFrameChange(getFormattedTime(current/(int)m_player->getFrameRate()));
}


void Controller::controlOnUpdatePlayer(QImage img)
{
    if (!img.isNull())
        {
            emit controlUpdatePlayer(img,m_player->getCurrentFrame(),getFormattedTime( (int)(m_player->getCurrentFrame()/m_player->getOriginalFrameRate())));
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
                emit controlSuccededLoad(filename,m_player->getNumberOfFrames(),getFormattedTime( (int)(m_player->getNumberOfFrames()/m_player->getFrameRate())));
            }
    }
}

void Controller::controlOnChangeFrameRate(QString val)
{
    m_player->setFrameRate(val.toDouble()*m_player->getOriginalFrameRate());
}

void Controller::controlOnClickedStop()
{
    m_player->setCurrentFrame(0);
    m_player->Stop();
    m_playerState = false;
    emit controlStopPlay();
}

void Controller::controlOnOutputChanged(int index)
{
    emit controlOutputChanged(index);
}

void Controller::controlOnGammaChanged(double gamma)
{
    emit controlGammaChanged(gamma);
}

void Controller::controlOnThresholdChanged(int threshold)
{
    emit controlThresholdChanged(threshold);
}

void Controller::controlOnDilationChanged(int dilation)
{
    emit controlDilationChanged(dilation);
}

void Controller::controlOnErosionChanged(int erosion)
{
    emit controlErosionChanged(erosion);
}

void Controller::controlOnVehiculesCounted(int vehicules)
{
    emit controlVehiculesCounted(vehicules);
}
