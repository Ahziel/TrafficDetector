#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "views/mainwindow.h"
#include "processing/player.h"
#include "processing/trafficdetector.h"
#include "models/projectmodel.h"

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
    void controlStopPlay();
    void controlOutputChanged(int index);
    void controlGammaChanged(double gamma);
    void controlThresholdChanged(int threshold);
    void controlDilationChanged(int dilation);
    void controlErosionChanged(int erosion);
    void controlVehiculesCounted(int vehicules);
    void controlSendVideoName(QString filename);
    void sendChangedGamma(double gamma);
    void sendChangedThreshold(double threshold);
    void sendChangedErosion(int erosion);
    void sendChangedDilation(int dilation);

public slots:
    void controlOnOpenProject(QString filename);
    void controlOnSaveAsProject(QString filename);
    void controlOnClickedLoad();
    void controlOnClickedPlay();
    void controlOnSliderPressed();
    void controlOnSliderReleased();
    void controlOnSliderMoved(int);
    void controlOnUpdatePlayer(QImage img);
    void controlOnGetNameVideo(QString filename);
    void controlOnChangeFrameRate(QString);
    void controlOnClickedStop();
    void controlOnOutputChanged(int index);
    void controlOnGammaChanged(double gamma);
    void controlOnThresholdChanged(int threshold);
    void controlOnDilationChanged(int dilation);
    void controlOnErosionChanged(int erosion);
    void controlOnVehiculesCounted(int vehicules);
    void receiveChangedGamma(double gamma);
    void receiveChangedThreshold(double threshold);
    void receiveChangedDilation(int dilation);
    void receiveChangedErosion(int erosion);

private :
    MainWindow m_window;
    Player *m_player;
    TrafficDetector *m_trafficDetector;
    ProjectModel* m_projectModel;
    bool m_playerState;

};

#endif // CONTROLLER_H
