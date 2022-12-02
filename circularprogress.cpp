#include "circularprogress.h"
#include "circularprogressdelegate.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include <QHBoxLayout>
#include <QTimer>

CircularProgress::CircularProgress(QWidget *parent)
    : QProgressBar(parent)
{
    init();
}

CircularProgress::~CircularProgress()
{
}

void CircularProgress::setProgressType(ProgressType type)
{
    m_progressType = type;
    update();
}

CircularProgress::ProgressType CircularProgress::progressType() const
{
    return m_progressType;
}

void CircularProgress::setUseThemeColors(bool value)
{
    if (m_useThemeColors == value) {
        return;
    }

    m_useThemeColors = value;
    update();
}

bool CircularProgress::useThemeColors() const
{
    return m_useThemeColors;
}

void CircularProgress::setLineWidth(qreal width)
{
    m_penWidth = width;
    update();
    updateGeometry();
}

qreal CircularProgress::lineWidth() const
{
    return m_penWidth;
}

void CircularProgress::setSize(int size)
{
    m_size = size;
    update();
    updateGeometry();
}

int CircularProgress::size() const
{
    return m_size;
}

void CircularProgress::setColor(const QColor &color)
{
    m_color = color;
    update();
}

QColor CircularProgress::color() const
{
    if (m_useThemeColors || !m_color.isValid()) {
        return QColor(37,177,218);
    } else {
        return m_color;
    }
}

QSize CircularProgress::sizeHint() const
{
    const qreal s = m_size+m_penWidth+8;
    return QSize(s, s);
}

void CircularProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!isEnabled()){
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidthF(m_penWidth);
        pen.setColor(QColor(186,186,186));
        painter.setPen(pen);
        painter.drawLine(rect().center()-QPointF(20, 20), rect().center()+QPointF(20, 20));
        painter.drawLine(rect().center()+QPointF(20, -20), rect().center()-QPointF(20, -20));
        return;
    }

    if (IndeterminateProgress == m_progressType){
        painter.translate(width()/2, height()/2);
        painter.rotate(m_delegate->angle());
    }

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(m_penWidth);

    // 绘制底部环
    pen.setColor(QColor(165,165,165));
    painter.setPen(pen);
    painter.drawEllipse(QPoint(0, 0), m_size / 2, m_size / 2);

    pen.setColor(color());

    if (IndeterminateProgress == m_progressType){
        QVector<qreal> pattern;
        pattern << m_delegate->dashLength()*m_size/50 << 30*m_size/50;

        pen.setDashOffset(m_delegate->dashOffset()*m_size / 50);
        pen.setDashPattern(pattern);

        painter.setPen(pen);

        painter.drawEllipse(QPoint(0, 0), m_size/2, m_size/2);
    }
    else
    {
        painter.setPen(pen);

        const qreal x = (width()-m_size)/2;
        const qreal y = (height()-m_size)/2;

        const qreal a = 360*(value()-minimum())/(maximum()-minimum());

        QPainterPath path;
        path.arcMoveTo(x, y, m_size, m_size, 0);
        path.arcTo(x, y, m_size, m_size, 0, a);

        painter.drawPath(path);
    }
}

void CircularProgress::init()
{
    m_delegate = new CircularProgressDelegate(this);
    m_progressType = IndeterminateProgress;
    m_penWidth = 6.25;
    m_size = 64;
    m_useThemeColors = true;

    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
        QSizePolicy::MinimumExpanding));

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->setLoopCount(-1);

    QPropertyAnimation *animation;
    animation = new QPropertyAnimation(this);
    animation->setPropertyName("dashLength");
    animation->setTargetObject(m_delegate);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setStartValue(0.1);
    animation->setKeyValueAt(0.15, 0.2);
    animation->setKeyValueAt(0.6, 20);
    animation->setKeyValueAt(0.7, 20);
    animation->setEndValue(20);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(this);
    animation->setPropertyName("dashOffset");
    animation->setTargetObject(m_delegate);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setStartValue(0);
    animation->setKeyValueAt(0.15, 0);
    animation->setKeyValueAt(0.6, -7);
    animation->setKeyValueAt(0.7, -7);
    animation->setEndValue(-25);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(this);
    animation->setPropertyName("angle");
    animation->setTargetObject(m_delegate);
    animation->setStartValue(0);
    animation->setEndValue(719);
    animation->setDuration(2050);

    group->addAnimation(animation);

    group->start();
}
