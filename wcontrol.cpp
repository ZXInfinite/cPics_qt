// Author: ZXInfinite

#include "wcontrol.h"
#define STDPRINT qDebug()

wControl::wControl(QApplication *app, QWidget *parent)
    : QMainWindow{parent}
{
    m_app = app;
    this->setWindowTitle("cPics - Control");
    this->resize(500,300);



// ------------This.MenuBar-------------

    m_menubar = this->menuBar();
    QAction *menuExit = new QAction("Exit");
    m_menubar->addAction(menuExit);
    connect(menuExit, &QAction::triggered, [&](){
        m_Exit(0);
    });

// ----------------End------------------



// --------------SysTray----------------

    m_SysTray_menu = new QMenu;
    QAction *sys_show, *sys_exit;

    sys_show = new QAction("显示控制面板");
    connect(sys_show, &QAction::triggered, [&](){
        wControl::show();
    });
    m_SysTray_menu->addAction(sys_show);

    sys_exit = new QAction("退出");
    connect(sys_exit, &QAction::triggered, [&](){
        m_Exit(0);
    });
    m_SysTray_menu->addAction(sys_exit);


    m_SysTray = new QSystemTrayIcon();
    if (m_SysTray != nullptr)
    {
        m_SysTray->setIcon(QIcon(":/ICO/ico/Ninebox.ico"));
        m_SysTray->setToolTip("cPics");
        m_SysTray->show();
        m_SysTray->setContextMenu(m_SysTray_menu);

        connect(m_SysTray, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason r){
            if(r == QSystemTrayIcon::ActivationReason::Trigger){
                if(this->isHidden())
                    this->show();
                else
                    this->hide();
            }
        });
    }

// ----------------End------------------


    init();


// --------------Set Table--------------

    m_table = new QTableWidget(this);
    m_table->move(0,this->menuBar()->height());
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels(QStringList() << "Num" <<"path"<<"is_show"<<"pos");//添加横向表头
    m_table->verticalHeader()->setVisible(true);//纵向表头可视化
    m_table->horizontalHeader()->setVisible(true);//横向表头可视化
    m_table->setShowGrid(false);//隐藏栅格
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
//    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
//    m_table->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
//    m_table->setStyleSheet("selection-background-color:graw");//设置选中颜色
    m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条

    SetTable();

// ----------------End------------------

}
wControl::~wControl()
{
    for(auto p : m_item){
        SaveInfo(p->i_num);
        delete p;
    }
    this->m_item.clear();

    for(auto p : m_item_che){
        delete p;
    }
    this->m_item_che.clear();

    for(auto p : m_SysTray_menu->actions()){
        delete p;
    }
    delete this->m_SysTray_menu;

    for(auto p : m_menubar->actions()){
        delete p;
    }
    // delete this->m_menubar;

    delete this->m_SysTray;
    delete this->m_info;
}



// --------Define init func-------------

void wControl::init()
{
    STDPRINT << "{LOG}> [Doing] Open Info FIle [cPics_ini]";

    m_info = new QSettings("cPics_ini", QSettings::IniFormat);
    if (m_info == nullptr)
    {
        STDPRINT << "[LOG]> [Error] Open Info FIle [cPics_ini] -> Result nullptr";
        STDPRINT << "[LOG]> [Exit] Close this program.";
        this->m_Exit(-1);
    }
    STDPRINT << "[LOG]> [Success] Open Info FIle [cPics_ini]";


    m_num = m_info->value("/Info/Num").toInt();

    for(int i=0;i<m_num;i++) NewItem(i);

}

// ---------------End-------------------



// -----------Function func------------

#define getmInfo(i, info) m_info->value("/" + QString::number(i) + "/" + info)
#define getItemPath(i) m_info->value("/" + QString::number(i) + "/Picture_Path").toString()
#define getItemTitle(i) m_info->value("/" + QString::number(i) + "/Title").isValid()?m_info->value("/" + QString::number(i) + "/Title").toString():nullptr
#define getItemX(i) m_info->value("/" + QString::number(i) + "/x").toInt()
#define getItemY(i) m_info->value("/" + QString::number(i) + "/y").toInt()
#define getItemScaled(i) m_info->value("/" + QString::number(i) + "/Scaled").toDouble()

void wControl::NewItem(int i)
{
    static vQLabel *p;
    p = new vQLabel(i,getItemPath(i), getItemTitle(i), getItemScaled(i));
    m_item.emplace_back(p);

    if(m_info->value("/" + QString::number(i) + "/is_show").toBool())
        p->show();
    else
        p->hide();

    p->move(getItemX(i),getItemY(i));

}

void wControl::SaveInfo(int i)
{
    m_info->setValue("/" + QString::number(i) + "/Picture_Path", m_item[i]->m_path);
    m_info->setValue("/" + QString::number(i) + "/is_show", !m_item[i]->isHidden());
    m_info->setValue("/" + QString::number(i) + "/x", m_item[i]->x());
    m_info->setValue("/" + QString::number(i) + "/y", m_item[i]->y());
    m_info->setValue("/" + QString::number(i) + "/Scaled", m_item[i]->GetScaled());
    m_info->sync();
}

// ---------------End-------------------



// ------------UI func------------------
void wControl::SetTable()
{
    m_table->setRowCount(m_num);
    m_table->setColumnWidth(0,50);
    m_table->setColumnWidth(1,270);
    m_table->setColumnWidth(2,70);
    m_table->setColumnWidth(3,70);

    QCheckBox *tChe;

    for(int rows=0;rows<m_num;rows++)
    {
        m_table->setItem(rows,0,new QTableWidgetItem(QString::number(rows)));
        m_table->setItem(rows,1,new QTableWidgetItem(m_item[rows]->m_path));
//        m_table->setItem(rows,2,new QTableWidgetItem(m_item[rows]->m_isshow?"True":"False"));

        tChe = new QCheckBox();
        m_item_che.push_back(tChe);
        tChe->setCheckState(m_item[rows]->isHidden()?Qt::Unchecked:Qt::Checked);

        connect(tChe, &QCheckBox::stateChanged, this, &wControl::OnCheck_StatusChanged);

        m_table->setCellWidget(rows,2,tChe);
        m_table->setItem(rows,3,new QTableWidgetItem(QString::number(m_item[rows]->x()) + ", " + QString::number(m_item[rows]->y())));
        m_table->setRowHeight(rows,30);
    }

    for(int rows=0;rows<m_num;rows++)
    {
        for(int columns=0;columns<4;columns++)
        {
//            m_table->item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
//            m_table->item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
//            m_table->item(rows,columns)->setBackground(QColor(85,170,255));//设置前景颜色
//            m_table->item(rows,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
        }
    }
/*
//    m_table->setSpan(2, 2,2 ,1);//合并单元格
//    m_table->setItem(2, 2, new QTableWidgetItem(QIcon("E:\\Qt_Project\\QTableWidget\\1.jpg"), "路飞"));//插入图片


    QString strText = ui->qTableWidget->item(1, 1)->text();//获取单元格的内容
    qDebug()<<"单元格内容："<<strText;//输出单元格内容

    //设置列标签
    QStringList HStrList;
    HStrList.push_back(QString("id"));
    HStrList.push_back(QString("name"));
    HStrList.push_back(QString("sex"));
    HStrList.push_back(QString("city"));
    HStrList.push_back(QString("other"));
    //设置行列数(只有列存在的前提下，才可以设置列标签)
    int HlableCnt = HStrList.count();
    ui->qTableWidget->setRowCount(10);
    ui->qTableWidget->setColumnCount(HlableCnt);
    //设置列标签
    ui->qTableWidget->setHorizontalHeaderLabels(HStrList);
    //具体单元格中添加ComboBox控件，下拉列表
    QComboBox *comBox = new QComboBox();
    comBox->addItem("成都");
    comBox->addItem("重庆");
    ui->qTableWidget->setCellWidget(0,3,comBox);*/


    //设置行和列的大小设为与内容相匹配（如果设置了宽高就不要用了）
//    m_table->resizeColumnsToContents();
//    m_table->resizeRowsToContents();
    m_table->resize(this->size());
}

void wControl::OnCheck_StatusChanged(int state)
{
    int pnum = (std::find(m_item_che.begin(),m_item_che.end(),sender()) - m_item_che.begin());

    if(state == 2)
        m_item[pnum]->show();
    else
        m_item[pnum]->hide();
}

// ---------------End-------------------



void wControl::m_Exit(int retcode)
{
    m_app->exit(retcode);
}
