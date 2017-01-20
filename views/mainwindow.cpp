#include "views/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creation();
    createConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createConnection()
{
    connect(ui->loadButton,SIGNAL(clicked()),this,SLOT(viewOnClickedLoad()));
    connect(ui->playButton,SIGNAL(clicked()),this,SLOT(viewOnClickedPlay()));
    connect(ui->horizontalSlider,SIGNAL(sliderPressed()),this,SLOT(viewOnSliderPressed()));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(viewOnSliderReleased()));
<<<<<<< HEAD
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(viewOnSliderMoved(int)));
    connect(ui->frameRate,SIGNAL(currentIndexChanged(QString)),this,SLOT(viewOnChangeFrameRate(QString)));
=======
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)), this, SLOT(viewOnSliderMoved(int)));
    connect(ui->frameRate,SIGNAL(valueChanged(double)),this,SLOT(viewOnChangeFrameRate(double)));
>>>>>>> aaa264186b44d580931f114b5567fe9a1424d912
}

void MainWindow::creation()
{
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->totalTime->setText("0:00:00");
    ui->currentTime->setText("0:00:00");
    QPixmap pixmap("/home/ahziel/Documents/ESIR2/IHM/TrafficDetector/play.png");
    QIcon ButtonIcon(pixmap);
    ui->playButton->setIcon(ButtonIcon);
    QPixmap pixmapStop("/home/ahziel/Documents/ESIR2/IHM/TrafficDetector/stop.png");
    QIcon ButtonIconStop(pixmapStop);
    ui->stopButton->setIcon(ButtonIconStop);

}

void MainWindow::viewOnClickedLoad()
{
    emit viewClickedLoad();
}

void MainWindow::viewOnClickedPlay()
{
    emit viewClickedPlay();
}

void MainWindow::viewOnClickedPause()
{
    emit viewClickedPause();
}

void MainWindow::viewOnLoadVideo()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                              tr("Open Video"), ".",
                                              tr("Video Files (*.avi *.mpg *.mp4)"));


    emit viewGetNameVideoLoad(filename);
}

void MainWindow::viewOnErrorLoad()
{
    QMessageBox msgBox;
    msgBox.setText("The selected video could not be opened!");
    msgBox.exec();
}

void MainWindow::viewOnChangeButtonPlay(bool play)
{
    if (play)
    {
        QPixmap pixmap("/home/ahziel/Documents/ESIR2/IHM/TrafficDetector/play.png");
        QIcon ButtonIcon(pixmap);
        ui->playButton->setIcon(ButtonIcon);
    }else
    {
        QPixmap pixmap("/home/ahziel/Documents/ESIR2/IHM/TrafficDetector/pause.png");
        QIcon ButtonIcon(pixmap);
        ui->playButton->setIcon(ButtonIcon);
    }
}

void MainWindow::viewOnSliderPressed()
{
    emit viewSliderPressed();
}

void MainWindow::viewOnSliderReleased()
{
    emit viewSliderReleased();
}

void MainWindow::viewOnSliderMoved(int current)
{
    emit viewSliderMoved(current);
}


void MainWindow::viewOnSuccededLoad(QString filename, double numberOfFrames, QString formatedTime)
{
    QFileInfo name = filename;
    this->setWindowTitle(name.fileName());
    ui->playButton->setEnabled(true);
    ui->horizontalSlider->setEnabled(true);
    ui->horizontalSlider->setMaximum(numberOfFrames);
    ui->totalTime->setText(formatedTime);
}

void MainWindow::viewOnUpdatePlayer(QImage img,double currentFrame, QString currentFrameText)
{
    ui->video->setAlignment(Qt::AlignCenter);
    ui->video->setPixmap(QPixmap::fromImage(img).scaled(ui->video->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    ui->horizontalSlider->setValue(currentFrame);
    ui->currentTime->setText(currentFrameText);
}

void MainWindow::viewOnProcessedFrame(QImage *frame)
{
    ui->video_2->setAlignment(Qt::AlignCenter);
    ui->video_2->setPixmap(QPixmap::fromImage(*frame).scaled(ui->video_2->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
}

void MainWindow::viewOnFrameChange(QString current)
{
    ui->currentTime->setText(current);
}

void MainWindow::viewOnChangeFrameRate(QString val)
{
    emit viewChangeFrameRate(val);
}
