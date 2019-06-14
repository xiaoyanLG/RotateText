#include "xyrotatetext.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

XYRotateText::XYRotateText(QWidget *parent)
    : QWidget(parent)
{
    mRotate = mStartAngle = mRotateAngle = 0;
    mRadius = 10;
}

void XYRotateText::setText(const QString &value)
{
    mText = value;
    updateImage();
}

void XYRotateText::setCenterPoint(const QPoint &value)
{
    mCenterPoint = value;
    updateImage();
}

void XYRotateText::setRotate(qreal value)
{
    mRotate = value;
    updateImage();
}

void XYRotateText::setStartAngle(int value)
{
    mStartAngle = value;
    updateImage();
}

void XYRotateText::setRadius(qreal value)
{
    mRadius = value;
    updateImage();
}

void XYRotateText::setRotateAngle(qreal value)
{
    mRotateAngle = value;
    update();
}

void XYRotateText::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QTransform form;
    form.translate(mCenterPoint.x(), mCenterPoint.y());
    form.rotate(mRotateAngle);
    painter.setTransform(form);

    painter.drawPixmap(QPoint(-mRadius, -mRadius), mTextPixmap);
}

double TwoPtDistance(const QPointF& pt1, const QPointF& pt2)
{return sqrt(double(pow(pt2.x() - pt1.x(), 2) + pow(pt2.y() - pt1.y(), 2)));}

bool XYRotateText::event(QEvent *event)
{
    static bool pressed = false;
    static QPoint pressedPos;
    switch (event->type())
    {
    case QEvent::MouseButtonPress:
        pressedPos = static_cast<QMouseEvent *>(event)->pos();
        if (TwoPtDistance(pressedPos, mCenterPoint) < mRadius) {
            pressed = true;
        }
        break;
    case QEvent::MouseButtonRelease:
        pressed = false;
        break;
    case QEvent::MouseMove:
        if (pressed) {
            QPoint pos = static_cast<QMouseEvent *>(event)->pos();
            mCenterPoint += pos - pressedPos;
            pressedPos = pos;
            update();
        }
        break;
    }

    return QWidget::event(event);
}

void XYRotateText::updateImage()
{
    auto w = mRadius * 2;
    mTextPixmap = QPixmap(w, w);
    mTextPixmap.fill(Qt::transparent);
    QPainter painter(&mTextPixmap);
    painter.setRenderHints(QPainter::TextAntialiasing);

    QTransform form;
    form.translate(mRadius, mRadius);
    QFontMetrics me(painter.font());
    QPainterPath path;
    path.addEllipse(mTextPixmap.rect().adjusted(me.height(), me.height(),
                                                -me.height(), -me.height()));
    QPointF start = path.pointAtPercent((int(mStartAngle) % 360) / 360.0);
    start -= QPoint(mRadius, mRadius);
    for (int i = 0; i < mText.size(); ++i)
    {
        form.rotate(mRotate);
        painter.setTransform(form);
        painter.drawText(start, mText.at(i));
    }

    update();
}
