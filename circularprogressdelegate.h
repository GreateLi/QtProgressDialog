#ifndef CIRCULARPROGRESSDELEGATE_H
#define CIRCULARPROGRESSDELEGATE_H

#include <QObject>
#include <QEvent>
#include <QProgressBar>
class CircularProgress;
class CircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
    Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
    CircularProgressDelegate(CircularProgress *parent);
    ~CircularProgressDelegate();

    void setDashOffset(qreal offset);
    qreal dashOffset() const;

    void setDashLength(qreal length);
    qreal dashLength() const;

    void setAngle(int angle);
    int angle() const;

private:
    Q_DISABLE_COPY(CircularProgressDelegate)

    CircularProgress *const m_progress;
    qreal m_dashOffset;
    qreal m_dashLength;
    int m_angle;
};


#endif // CIRCULARPROGRESSDELEGATE_H
