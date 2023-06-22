// Author: ZXInfinite

#include "clabitem.h"

cLabItem::cLabItem(const int &num, QSettings *stream, QWidget *parent)
{
    this->m_num = num;
    this->m_setting = stream;
    this->m_parent = parent;
}
cLabItem::~cLabItem()
{
    if(m_Gotinfo){
        Update_data();
        SetInfo();
    }
}


void cLabItem::GetInfo(){this->GetInfo(this->m_setting);}
void cLabItem::GetInfo(QSettings* stream)
{
    this->m_fpath = stream->value("/" + QString::number(this->m_num) + "/Picture_Path").toString();
    this->m_isshow = stream->value("/" + QString::number(this->m_num) + "/is_show").toBool();
    this->m_pos.setX(stream->value("/" + QString::number(this->m_num) + "/x").toInt());
    this->m_pos.setY(stream->value("/" + QString::number(this->m_num) + "/y").toInt());
    m_info_changed = true;
    m_Gotinfo = true;
}

void cLabItem::SetInfo(){this->SetInfo(this->m_setting);}
void cLabItem::SetInfo(QSettings* stream)
{
    stream->setValue("/" + QString::number(this->m_num) + "/Picture_Path", this->m_fpath);
    stream->setValue("/" + QString::number(this->m_num) + "/is_show", this->m_isshow);
    stream->setValue("/" + QString::number(this->m_num) + "/x", this->m_pos.x());
    stream->setValue("/" + QString::number(this->m_num) + "/y", this->m_pos.y());
    stream->sync();
}
void cLabItem::Update_data()
{
//    is_show = ;
    this->m_pos = m_wlab->pos();
}

void cLabItem::change(const QString &fpath){this->m_fpath = fpath;}
void cLabItem::change(const QString &fpath, const bool &isshow){this->m_fpath = fpath;this->m_isshow = isshow;}
void cLabItem::change(const QString &fpath, const bool &isshow, const QPoint &pos){this->m_fpath = fpath;this->m_isshow = isshow;this->m_pos = pos;}
void cLabItem::change(const QString &fpath, const bool &isshow, const QPoint &pos, const int &num){this->m_fpath = fpath;this->m_isshow = isshow;this->m_pos = pos;this->m_num = num;}

void cLabItem::show(){m_isshow = true;}
void cLabItem::hide(){m_isshow = false;}

void cLabItem::update()
{
    if(!m_winited){
        m_wlab = new wLable(this->m_fpath, this->m_parent);
        m_wlab->move(this->m_pos);
        m_info_changed = false;
    }
    else if(m_info_changed){
        m_wlab->set_vLable(m_fpath);
        m_wlab->move(this->m_pos);
        m_info_changed = false;
    }

    if(m_isshow)
        m_wlab->wshow();
    else
        m_wlab->whide();
}
