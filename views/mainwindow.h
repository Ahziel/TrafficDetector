#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTime>


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

    void createConnection();
    void creation();

public slots:
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

signals :
    void viewClickedLoad();
    void viewClickedPlay();
    void viewClickedPause();
    void viewSliderPressed();
    void viewSliderReleased();
    void viewSliderMoved(int);
    void viewChangeFrameRate(QString);
    void viewGetNameVideoLoad(QString filename);


};

#endif // MAINWINDOW_H
