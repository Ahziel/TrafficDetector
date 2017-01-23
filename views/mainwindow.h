#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTime>
#include <QTextEdit>
#include <QMessageBox>
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QLCDNumber>

#include "help.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Help *helpwindow;

    void createConnection();
    void creation();

public slots:
    void viewOnOpenProject();
    void viewOnSaveAsProject();
    void viewOnClickedLoad();
    void viewOnClickedPlay();
    void viewOnClickedPause();
    void viewOnLoadVideo();
    void viewOnErrorLoad();
    void viewOnChangeButtonPlay(bool);
    void viewOnSliderPressed();
    void viewOnSliderReleased();
    void viewOnSliderMoved(int current);
    void viewOnSuccededLoad(QString filename, double numberOfFrames, QString formatedTime);
    void viewOnUpdatePlayer(QImage img,double currentFrame, QString currentFrameText);
    void viewOnProcessedFrame(QImage* frame);
    void viewOnFrameChange(QString);
    void viewOnChangeFrameRate(QString);
    void viewOnClickedStop();
    void viewOnStop();
    void viewOnHelp();
    void viewOnAbout();
    void viewOnHelpQuit();
    void viewOnOutputChanged(int index);
    void viewOnGammaChanged(double gamma);
    void viewOnThresholdChanged(int threshold);
    void viewOnDilationChanged(int dilation);
    void viewOnErosionChanged(int erosion);
    void viewOnCountedVehicules(int vehicules);

signals :
    void viewOpenProject(QString filename);
    void viewSaveAsProject(QString filename);
    void viewClickedLoad();
    void viewClickedPlay();
    void viewClickedPause();
    void viewSliderPressed();
    void viewSliderReleased();
    void viewSliderMoved(int);
    void viewChangeFrameRate(QString);
    void viewGetNameVideoLoad(QString filename);
    void viewClickedStop();
    void viewGammaChanged(double gamma);
    void viewThresholdChanged(int threshold);
    void viewDilationChanged(int dilation);
    void viewErosionChanged(int erosion);
    void viewOutputChanged(int index);

};

#endif // MAINWINDOW_H
