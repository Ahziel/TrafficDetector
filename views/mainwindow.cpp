#include "views/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    connect(ui->pauseButton,SIGNAL(clicked()),this,SLOT(viewOnClickedPause()));
}

void MainWindow::viewOnClickedLoad()
{
    emit viewOnClickedLoad();
}

void MainWindow::viewOnClickedPlay()
{
    emit viewOnClickedPlay();
}

void MainWindow::viewOnClickedPause()
{
    emit viewOnClickedPause();
}
