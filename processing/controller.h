#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "views/mainwindow.h"
#include "player.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(MainWindow* window,QObject *parent = 0);

    void createConnection();
    void startApplication();

signals:
    void controlOpenLoadVideo();
    void controlErrorLoad();
    void controlSuccededLoad(QString filename, double numberOfFrames, double frameRate);


public slots:
    void controlOnClickedLoad();
    void controlOnClickedPlay();
    void controlOnClickedPause();
    void controlOnProcessedImage();
    void controlOnGetNameVideo(QString filename);

private :
    MainWindow m_window;
    Player *m_player;

};

#endif // CONTROLLER_H
