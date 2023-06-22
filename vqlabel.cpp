// Author: ZXInfinite

#include "vqlabel.h"

vQLabel::vQLabel(QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f)
{
}
vQLabel::vQLabel(const QString &text, QWidget *parent, Qt::WindowFlags f) : QLabel(text, parent, f)
{
}

void vQLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mlPos = QCursor().pos();
        m_lwinPos = this->parentWidget()->pos();
    }
    else if (event->button() == Qt::MiddleButton)
    {
        this->parentWidget()->close();
    }
    QLabel::mousePressEvent(event);
}

void vQLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        this->parentWidget()->move(m_lwinPos + QCursor().pos() - m_mlPos);
    }
    QLabel::mouseMoveEvent(event);
}

void vQLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
}

void vQLabel::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
    { // 滚轮远离使用者
        // 放大
        this->resize(this->size() * 1.1);
        this->move(0, 0);
        this->parentWidget()->resize(this->size());
        this->parentWidget()->move(this->parentWidget()->pos() - event->position().toPoint() * 0.1);
    }
    else
    { // 滚轮向使用者
        // 缩小
        this->resize(this->size() * 0.9);
        this->move(0, 0);
        this->parentWidget()->resize(this->size());
        this->parentWidget()->move(this->parentWidget()->pos() + event->position().toPoint() * 0.1);
    }
}
