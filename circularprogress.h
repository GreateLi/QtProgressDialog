#ifndef CIRCULARPROGRESS_H
#define CIRCULARPROGRESS_H

#include <QEvent>
#include <QProgressBar>

class CircularProgressDelegate;
class CircularProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(qreal lineWidth WRITE setLineWidth READ lineWidth)
    Q_PROPERTY(qreal size WRITE setSize READ size)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    explicit CircularProgress(QWidget *parent = nullptr);
    ~CircularProgress();

    enum ProgressType {
        DeterminateProgress, // 普通进度条
        IndeterminateProgress // 等待进度条
    };

    void setProgressType(ProgressType type);
    CircularProgress::ProgressType progressType() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setLineWidth(qreal width);
    qreal lineWidth() const;

    void setSize(int size);
    int size() const;

    void setColor(const QColor &color);
    QColor color() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void init();

private:
    CircularProgressDelegate * m_delegate;
    ProgressType m_progressType;
    QColor m_color;
    qreal m_penWidth;
    int m_size;
    bool m_useThemeColors;
};
#endif // CIRCULARPROGRESS_H
