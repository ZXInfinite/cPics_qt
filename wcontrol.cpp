// Author: ZXInfinite

#include "wcontrol.h"

wControl::wControl(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("cPics - Control");
    this->resize(500,300);

    init();
    GetInfo_child();
}
wControl::~wControl()
{
    for(auto p : m_item){
        delete p;
//        p.SetInfo();
    }
    this->m_item.clear();
}

void wControl::init()
{
    if (!OpenInfofile())
    {
        qDebug() << "[LOG]> [Error] OpenInfofIle -> Result false";
        qDebug() << "[LOG]> [Exit] Close this program.";
        this->close();
    }

    if (!GetInfo())
    {
        qDebug() << "[LOG]> [Call] Set Default Info(True)";
//        SetInfo(true);
//        qDebug() << "[LOG]> [Exit] To close because it didn't open anything.";
//        this->close();
    }
}

bool wControl::OpenInfofile()
{
    //    QFile aFile("cPics_info");
    //    if (!aFile.exists())
    //        return false;
    //    if (!aFile.open(QIODevice::ReadWrite | QIODevice::Text))
    //        return false;
    //    return true;

    qDebug() << "{LOG}> [Doing] Open Info FIle [cPics_ini]";
    m_info = new QSettings("cPics_ini", QSettings::IniFormat);
    if (m_info != nullptr)
    {
        qDebug() << "[LOG]> [Success] Open Info FIle [cPics_ini]";
        return true;
    }
    else
    {
        qDebug() << "[LOG]> [Error] Open Info FIle [cPics_ini] -> Result nullptr";
        return false;
    }
}

bool wControl::GetInfo()
{
    m_num = m_info->value("/Info/Num").toInt();
    return true;
}
bool wControl::GetInfo_child(const int &num)
{
    for(int i=0;i<m_num;i++){
        m_item.push_back(new cLabItem(i,m_info, this->parentWidget()));
        m_item[i]->GetInfo();
        m_item[i]->update();
    }
    return true;
}
