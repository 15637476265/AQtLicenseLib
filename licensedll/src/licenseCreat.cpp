#include "licenseCreat.h"
#include <QCryptographicHash>
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QDir>

QString LicenseCreat::creatLicenseStr(QString processorID, QString result)
{
    QString originStr = processorID + result;

    QByteArray md5;
    md5 = QCryptographicHash::hash(originStr.toLatin1(),QCryptographicHash::Md5);
    return  QString(md5.toHex());
}

void LicenseCreat::creatLicenseFile(QString path, QString fileName,QString stream)
{
    QFile file(path + fileName);
    QDir tempDir;
    if(!tempDir.exists(path))
    {
        tempDir.mkpath(path);
    }
    QByteArray str = stream.toUtf8();
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.write(str);

    file.close();
}
