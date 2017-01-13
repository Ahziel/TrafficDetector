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

public slots:
    void controlOnClickedLoad();
    void controlOnClickedPlay();
    void controlOnClickedPause();
    void controlOnProcessedImage();

private :
    MainWindow m_window;
    Player *m_player;

};

#endif // CONTROLLER_H
