#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QtConcurrent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mDialog = new  DialogProgress(this);
    setWindowState(Qt::WindowMaximized);

//    QProgressBar *m_pLeftToRightProBar = new QProgressBar(this);

//    m_pLeftToRightProBar->setValue(-1);
//    ui->horizontalLayout->addWidget(m_pLeftToRightProBar);

    QTimer::singleShot(100,this,[=](){
                       qDebug()<<"aaaaa";
                   });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showbtn_clicked()
{
   // progress->start();
    mDialog->show();
}

void MainWindow::on_hidebtn_clicked()
{
   // progress->stop(true);
    mDialog->hide();
}
