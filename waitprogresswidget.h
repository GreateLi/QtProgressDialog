#ifndef WAITPROGRESSWIDGET_H
#define WAITPROGRESSWIDGET_H

#include <QWidget>
#include<QTimer>
#include<QHBoxLayout>
#include "circularprogress.h"
class WaitProgressWidget : public QWidget
{
    Q_OBJECT

public:
    WaitProgressWidget(QWidget *parent);
    ~WaitProgressWidget();
    void setBgColor(QColor color);

    void start(int msec = 60000);
    void stop(bool isOk);

signals:
    void sig_finished(bool isOk);

private:
    void show();// 限制外部调用show hide
    void hide();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
    void showEvent(QShowEvent *ev);

private:
    CircularProgress* m_progress;
    QWidget* m_parentWidget;
    QTimer* m_timer;
};


#endif // WAITPROGRESSWIDGET_H
