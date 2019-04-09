#ifndef LICENSE_H
#define LICENSE_H

#include "licensedll_global.h"
#include "src/LicenseOperation.h"
#include <QObject>


class LICENSEDLLSHARED_EXPORT License: public QObject
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
