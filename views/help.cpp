#include "help.h"
#include "ui_help.h"

Help::Help(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    emit helpQuit();
}
