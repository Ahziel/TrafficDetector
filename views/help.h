#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Help;
}

class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QDialog *parent = 0);
    ~Help();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Help *ui;

signals:
    void helpQuit();
};

#endif // HELP_H
