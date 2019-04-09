#include "widget.h"
#include <QApplication>
#include "License.h"
#include <QDebug>
#include <QSplashScreen>
#include <QDateTime>


int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("ZXXLicense0");
    QGuiApplication::setOrganizationName("ZXXLicense0");
    QApplication a(argc, argv);

    QPixmap pixmap(":res/splash/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);

    QFont sansFont("Helvetica [Cronyx]", 32);
    splash->setFont(sansFont);
    splash->show();


    splash->showMessage("验证license.........",Qt::AlignCenter,Qt::white);
    qApp->processEvents();

    License sssss;
    sssss.init(7);

    bool result = sssss.startCheck();
    if(result){
        splash->showMessage("剩余可用时间"+QString::number(sssss.getLicenseDays()),Qt::AlignCenter,Qt::green);
        qApp->processEvents();

        QDateTime n=QDateTime::currentDateTime();
        QDateTime now;
        do{
        now=QDateTime::currentDateTime();
        }
        while (n.secsTo(now)<=4);
        Widget w;
        w.show();
        w.setLicenseDays(sssss.getLicenseDays());
        splash->finish(&w);

        delete splash;
        return a.exec();

    }else {
        splash->showMessage("找不到有效的license文件!",Qt::AlignCenter,Qt::red);
        qApp->processEvents();
        QDateTime n=QDateTime::currentDateTime();
        QDateTime now;
        do{
        now=QDateTime::currentDateTime();
        }
        while (n.secsTo(now)<=1);

        splash->close();
        delete splash;
        qApp->exit(0);
    }


}
