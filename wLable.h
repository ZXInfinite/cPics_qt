// Author: ZXInfinite

#ifndef WLABLE_H
#define WLABLE_H

#include <QMainWindow>
#include "vqlabel.h"

class wLable : public QMainWindow

{
    Q_OBJECT

public:
    wLable(const QString &fpath, QWidget *parent = nullptr);
    ~wLable();

    void wshow();
    void whide();

    bool set_vLable(const QString &fpath);

private:
    vQLabel *mlab;
    bool m_normal = false;
};

#endif // WLABLE_H
