#include "licenseread.h"
#include <QFile>
#include <QDebug>

QString LicenseRead::readFileLicense(QString path, QString filename)
{
    qDebug()<<"path--->"<<path + filename;
    QByteArray t;
    QFile file(path + filename);
    if(!file.exists()){
        t.push_back("N");
    }else {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        t = file.readAll();
        file.close();
    }

    return  QString(t);
}
