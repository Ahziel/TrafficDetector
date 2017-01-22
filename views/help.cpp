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

/*
 * Function that take the address of a text file and put it in the label
 *
 */
void Help::setText(QString address)
{
    ui->label->setText(readFile(address));
}



QString Help::readFile(QString filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     return NULL;
  }

  QByteArray total;
  QByteArray line;
  while (!file.atEnd()) {
     line = file.read(1024);
     total.append(line);
  }

  return QString(total);
}


