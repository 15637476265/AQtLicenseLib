#ifndef LICENSECREAT_H
#define LICENSECREAT_H

#include <QObject>

class LicenseCreat
{
public:
    //通过处理器的ID和时间校验结果来生成MD5序列号
    static QString creatLicenseStr(QString processorID,QString result);
    static void creatLicenseFile(QString path,QString fileName,QString stream);

};

#endif // LICENSECREAT_H
