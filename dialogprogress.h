#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "waitprogresswidget.h"
namespace Ui {
class Dialog;
}

class DialogProgress : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProgress(QWidget *parent = nullptr);
    ~DialogProgress();

private:
    Ui::Dialog *ui;
    WaitProgressWidget* progress;
};

#endif // DIALOG_H
