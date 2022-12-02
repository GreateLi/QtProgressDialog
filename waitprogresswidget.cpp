#include "waitprogresswidget.h"

WaitProgressWidget::WaitProgressWidget(QWidget *parent)
    : QWidget(parent)
    , m_parentWidget(parent)
{
    m_progress = new CircularProgress(this);

    this->setAutoFillBackground(true);
    this->hide();

    QColor color(165,165,165);
    color.setAlphaF(0.6);
    this->setBgColor(color);

    auto waitBgLayout = new QHBoxLayout(this);
    waitBgLayout->addWidget(m_progress);
    waitBgLayout->setAlignment(m_progress, Qt::AlignCenter);

    parent->installEventFilter(this);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        if(!this->isHidden()){
            stop(false);
        }
    });
}

WaitProgressWidget::~WaitProgressWidget()
{

}

void WaitProgressWidget::setBgColor(QColor color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    this->setPalette(palette);
    update();
}

bool WaitProgressWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == m_parentWidget && ev->type() == QEvent::Resize){
        if(!this->isHidden()){
            this->setFixedSize(m_parentWidget->size());
            this->raise();
        }
    }
    return QWidget::eventFilter(obj,ev);
}

void WaitProgressWidget::showEvent(QShowEvent *ev)
{
    Q_UNUSED(ev);

    this->setFixedSize(m_parentWidget->size());
    this->raise();
}

void WaitProgressWidget::start(int msecs)
{
    m_timer->start(msecs);
    this->show();
}

void WaitProgressWidget::stop(bool isOk)
{
    m_timer->stop();
    this->hide();
    emit sig_finished(isOk);
}

void WaitProgressWidget::show()
{
    QWidget::show();
}

void WaitProgressWidget::hide()
{
    QWidget::hide();
}

