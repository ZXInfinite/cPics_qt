// Author: ZXInfinite

#include "wcontrol.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
        QSplashScreen *splash = new QSplashScreen;
        splash->setPixmap(QPixmap("T1.png"));
        splash->show();
        Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
        splash->showMessage(QObject::tr("Setting up the main window..."),topRight, Qt::white);//Show Info
    */

    wControl w(&a,nullptr);
    // w.show();

    return a.exec();
}
