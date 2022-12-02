#include "dialogprogress.h"
#include "ui_dialog.h"

DialogProgress::DialogProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    progress = new WaitProgressWidget(this);
    ui->horizontalLayout->addWidget(progress);
    progress->start();
}

DialogProgress::~DialogProgress()
{
    delete ui;
}
