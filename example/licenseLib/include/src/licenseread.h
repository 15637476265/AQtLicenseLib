#ifndef LICENSEREAD_H
#define LICENSEREAD_H


#include <QObject>

class LicenseRead
{
public:

    //读取license字符串
    static QString readFileLicense(QString path,QString filename);

};
#endif // LICENSEREAD_H
