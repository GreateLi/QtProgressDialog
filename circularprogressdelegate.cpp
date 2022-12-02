#include "circularprogressdelegate.h"
#include "circularprogress.h"

CircularProgressDelegate::CircularProgressDelegate(CircularProgress *parent)
    : QObject(parent),
    m_progress(parent),
    m_dashOffset(0),
    m_dashLength(89),
    m_angle(0)
{
    Q_ASSERT(parent);
}

CircularProgressDelegate::~CircularProgressDelegate()
{
}

void CircularProgressDelegate::setDashOffset(qreal offset)
{
    m_dashOffset = offset;
    m_progress->update();
}

qreal CircularProgressDelegate::dashOffset() const
{
    return m_dashOffset;
}

void CircularProgressDelegate::setDashLength(qreal length)
{
    m_dashLength = length;
    m_progress->update();
}

qreal CircularProgressDelegate::dashLength() const
{
    return m_dashLength;
}

void CircularProgressDelegate::setAngle(int angle)
{
    m_angle = angle;
    m_progress->update();
}

int CircularProgressDelegate::angle() const
{
    return m_angle;
}
