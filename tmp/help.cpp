#include "help.h"
#include  "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //setWindowIcon(QIcon(QString::fromUtf8("/home/helena/Downloads/PAINy/MANKALA/Mancala20122/icon.jpg")));
}

Help::~Help()
{
    delete ui;
}
