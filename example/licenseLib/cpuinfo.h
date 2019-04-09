#ifndef CPUINFO
#define CPUINFO

#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "linuxfactory.h"

class CPUInfo{

public:
    static QString getCommand(){

        QString cmd;
#ifdef Q_OS_WIN
        cmd = "wmic cpu get name";
#else
        cmd = "cat /proc/cpuinfo";
#endif
        return cmd;
    }

    static QString getCPUInformation(const QVector<QString> strVec){

        QString cpuInfo = "NULL";

#ifdef Q_OS_WIN
        for(int i = 0;i < strVec.size(); i++){
            if(strVec[i].contains("CPU")){
                QString msg = strVec[i];
                cpuInfo =msg.remove("\r");
            }
        }
#else

        LinuxOperation *linuxOpera = NULL;

        try{
            linuxOpera = LinuxOperationFactory::createOperate("model name");

        }
        catch(QString err){

            QMessageBox::information(NULL, "info", err);
        }

        if(linuxOpera != NULL){

            cpuInfo = linuxOpera->getInfomation(strVec);
            delete linuxOpera;
        }

#endif

        return cpuInfo;
    }
};

#endif // CPUINFO

