#ifndef XYROTATETEXT_H
#define XYROTATETEXT_H

#include <QWidget>

class XYRotateText : public QWidget
{
    Q_OBJECT
public:
    explicit XYRotateText(QWidget *parent = 0);

    void setText(const QString &value);
    void setCenterPoint(const QPoint &value);
    void setRotate(qreal value);
    void setStartAngle(int value);
    void setRadius(qreal value);
    inline qreal rotateAngle() {return mRotateAngle; }
    void setRotateAngle(qreal value);

protected:
    void paintEvent(QPaintEvent *event);
    bool event(QEvent *event);

private:
    void updateImage();

private:
    QPixmap  mTextPixmap;
    QPoint   mCenterPoint;
    QString  mText;
    qreal    mRotate;
    qreal    mStartAngle;
    qreal    mRotateAngle;
    qreal    mRadius;

};

#endif // XYROTATETEXT_H
