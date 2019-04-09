#include "linuxOperation.h"
#include <QDebug>

LinuxOperation::~LinuxOperation()
{
    qDebug()<< "~LinuxOperation() called!";
}

QString OperationModelName::getInfomation(const QVector<QString> strVec){

    for(int i = 0; i < strVec.size(); i++){
        if(strVec[i].contains("model name")){
            //qDebug()<< strVec[i];
            QStringList list = strVec[i].split(":");
            return list[1];
        }
    }

    throw QString("can't find the model name");
}

OperationModelName::~OperationModelName(){

    qDebug()<< "~OperationModelName() called!";
}
