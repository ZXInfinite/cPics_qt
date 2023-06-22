// Author: ZXInfinite

#include "wLable.h"

wLable::wLable(const QString &fpath, QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); // 需要去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);

    mlab = new vQLabel(this);
    m_normal = set_vLable(fpath);

    if(m_normal){
        this->resize(mlab->size());
        this->show();
    }
}

wLable::~wLable()
{
    if (mlab != nullptr)
        delete mlab;
}

void wLable::wshow()
{
    if(m_normal)
        show();
}
void wLable::whide()
{
    if(m_normal)
        hide();
}

bool wLable::set_vLable(const QString &fpath)
{
    QPixmap pixmap(fpath);
    if (!pixmap)
    {
        qDebug() << "[LOG]> [Error] Couldn't open the picture -> " << fpath;
        return false;
    }
    else
    {
        qDebug() << "[LOG]> [Success] Open the picture -> " << fpath;
    }

    mlab->setPixmap(pixmap);
    mlab->setScaledContents(true); // 自适应大小

    mlab->resize(pixmap.size());
    mlab->move(0, 0);
    return true;
}
