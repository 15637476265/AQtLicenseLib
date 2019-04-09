#ifndef LICENSE_H
#define LICENSE_H

#include <QObject>
#include "src/LicenseOperation.h"

class License: public QObject
{
    Q_OBJECT
public:
    License(QObject *parent = nullptr);
    void    init(int days);
    bool    startCheck();
    int     getLicenseDays();
private:
    LicenseOperation object;
};

#endif // LICENSE_H
