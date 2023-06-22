// Author: ZXInfinite

#ifndef WCONTROL_H
#define WCONTROL_H


#include <QMainWindow>
#include <QSettings>
#include <vector>
#include "clabitem.h"

class wControl : public QMainWindow
{
    Q_OBJECT
public:
    explicit wControl(QWidget *parent = nullptr);
    ~wControl();

signals:

private:
    QSettings *m_info;
    int m_num = -1;
    std::vector<cLabItem *> m_item;

    void init();
    bool OpenInfofile();
    bool GetInfo();
    bool GetInfo_child(const int &num = -1);
};

#endif // WCONTROL_H
