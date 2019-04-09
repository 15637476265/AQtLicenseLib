#ifndef LICENSECHECK_H
#define LICENSECHECK_H

#include <QObject>

class LicenseCheck
{

public:
    static bool licenseCheck(QString target,QString local);
};

#endif // LICENSECHECK_H
