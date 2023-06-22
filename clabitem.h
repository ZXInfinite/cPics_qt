// Author: ZXInfinite

#ifndef CLABITEM_H
#define CLABITEM_H

#include <QString>
#include <QPoint>
#include <QSettings>
#include "wLable.h"

class cLabItem
{
public:
    cLabItem(const int &num, QSettings *stream,  QWidget *parent = nullptr);
    ~cLabItem();

    void GetInfo();
    void GetInfo(QSettings* stream);
    void SetInfo();
    void SetInfo(QSettings* stream);
    void change(const QString &fpath);
    void change(const QString &fpath, const bool &isshow);
    void change(const QString &fpath, const bool &isshow, const QPoint &pos);
    void change(const QString &fpath, const bool &isshow, const QPoint &pos, const int &num);

    void show();
    void hide();
    void update();

    void Update_data();
private:
    QWidget *m_parent;
    QSettings *m_setting;

    // Base Info
    int m_num = -1;
    QString m_fpath;
    bool m_isshow = true;
    QPoint m_pos;
    /*
        [Info]
        Num = 1

        [0]
        Picture_Path=\\cPics_qt\\ico\\Box.png
        is_show = true
        x=379
        y=295
    */

    // Window
    wLable *m_wlab;
    bool m_winited = false;
    bool m_info_changed = false;
    bool m_Gotinfo = false;
};



#endif // CLABITEM_H
