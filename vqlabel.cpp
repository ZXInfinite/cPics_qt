// Author: ZXInfinite

#include "vqlabel.h"

vQLabel::vQLabel(const int i, const QString &path, const QString &title, const double scaled, QWidget *parent, Qt::WindowFlags f) : QLabel(title, parent, f)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); // 需要去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    this->m_path = path;
    i_num = i;

    QPixmap tpixmap(path);
    this->setPixmap(tpixmap);
    setScaledContents(true);
    this->resize(tpixmap.size());

    if(title == nullptr)
        this->setWindowTitle(path);
    else
        this->setWindowTitle(title);

    m_sizeOriginal = this->size();
    this->resize(this->size()*(scaled<=0?1:scaled));
}

void vQLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mlPos = QCursor().pos();
        m_lwinPos = this->pos();
    }
    else if (event->button() == Qt::MiddleButton)
    {
        this->hide();
    }
    QLabel::mousePressEvent(event);
}

void vQLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        this->move(m_lwinPos + QCursor().pos() - m_mlPos);
    }
    QLabel::mouseMoveEvent(event);
}

void vQLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
}

void vQLabel::wheelEvent(QWheelEvent *event)
{
    static auto tlen = this->x() > this->y()?this->x():this->y();

    if(tlen<10)
        scx = 0.1;
    else if(tlen<100)
        scx=0.06;
    else if(tlen<1000)
        scx=0.04;
    else
        scx = 0.02;

//    qDebug()<<event->angleDelta();

    if (event->angleDelta().y() > 0)
    { // 滚轮远离使用者
        // 放大
        this->resize(this->size() * (1+scx));
        this->move(this->pos() - event->position().toPoint() * scx);
    }
    else
    { // 滚轮向使用者
        // 缩小
        this->resize(this->size() * (1-scx));
        this->move(this->pos() + event->position().toPoint() * scx);
    }
    m_sizeLast = this->size();
}

double vQLabel::GetScaled()
{
    return (double)this->size().height() / (double)m_sizeOriginal.height();
}
