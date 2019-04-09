#include "License.h"


License::License(QObject *parent) : QObject(parent)
{
}

void License::init(int days)
{
    object.initLicense(days);
}

bool License::startCheck()
{
    return object.startProcess();
}

int License::getLicenseDays()
{
    return object.getLicenseDays();
}
