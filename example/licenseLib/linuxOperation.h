#ifndef LINUXOPERATION_H
#define LINUXOPERATION_H

#include <QString>
#include <QVector>

class LinuxOperation
{
public:
    virtual QString getInfomation(const QVector<QString> strVec) = 0;
    virtual ~LinuxOperation();
};


class OperationModelName: public LinuxOperation{

public:
    QString getInfomation(const QVector<QString> strVec);
    ~OperationModelName();
};

#endif // LINUXOPERATION_H
