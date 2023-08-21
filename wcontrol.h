// Author: ZXInfinite

#ifndef WCONTROL_H
#define WCONTROL_H

#include <QApplication>
#include <QMainWindow>
#include <QSettings>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QCheckBox>
#include <QSystemTrayIcon>
#include <QMenuBar>

#include <vector>
#include <map>
#include "vqlabel.h"

class wControl : public QMainWindow
{
    Q_OBJECT
public:
    explicit wControl(QApplication *app, QWidget *parent = nullptr);
    ~wControl();

signals:

private:
    QTableWidget *m_table;
    QSystemTrayIcon *m_SysTray;
    QMenu *m_SysTray_menu;
    QMenuBar * m_menubar;
    QAction * m_menu_Exit;
    QApplication *m_app;

    QSettings *m_info;
    int m_num = -1;
    std::vector<vQLabel *> m_item;
    std::vector<QCheckBox *> m_item_che;

    void init();

    void NewItem(int i);
    void SaveInfo(int i);

    void SetTable();
    void m_Exit(int retcode = 0);

public slots:
    void OnCheck_StatusChanged(int state);
};

#endif // WCONTROL_H
