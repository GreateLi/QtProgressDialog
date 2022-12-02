#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dialogprogress.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_showbtn_clicked();

    void on_hidebtn_clicked();

private:
    Ui::MainWindow *ui;


    DialogProgress* mDialog;
};

#endif // MAINWINDOW_H
