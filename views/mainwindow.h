#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

public slots:
    void viewOnClickedLoad();
    void viewOnClickedPlay();
    void viewOnClickedPause();

signals :
    void viewClickedLoad();
    void viewClickedPlay();
    void viewClickedPause();

};

#endif // MAINWINDOW_H
