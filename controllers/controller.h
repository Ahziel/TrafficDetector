#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "views/mainwindow.h"
#include "processing/player.h"
#include "processing/trafficdetector.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(MainWindow* window,QObject *parent = 0);
    ~Controller();

    void createConnection();
    void startApplication();
    QString getFormattedTime(int timeInSeconds);

signals:
    void controlOpenLoadVideo();
    void controlErrorLoad();
    void controlSuccededLoad(QString filename, double numberOfFrames, QString formatedTime);
    void controlChangeButtonPlay(bool play);
    void controlUpdatePlayer(QImage img,double currentFrame, QString currentFrameText);
    void controlFrameChange(QString placement);


public slots:
    void controlOnClickedLoad();
    void controlOnClickedPlay();
    void controlOnSliderPressed();
    void controlOnSliderReleased();
    void controlOnSliderMoved(int);
    void controlOnUpdatePlayer(QImage img);
    void controlOnGetNameVideo(QString filename);
    void controlOnChangeFrameRate(double);

private :
    MainWindow m_window;
    Player *m_player;
    TrafficDetector *m_trafficDetector;

};

#endif // CONTROLLER_H
