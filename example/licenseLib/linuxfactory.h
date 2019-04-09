#ifndef LINUXFACTORY
#define LINUXFACTORY

#include "linuxOperation.h"

class LinuxOperationFactory{

public:
    static LinuxOperation *createOperate(const QString operateStr){

        LinuxOperation *linuxOperation;

        if(operateStr == "model name")
            linuxOperation = new OperationModelName;
        else
            throw QString("operateStr is error!");

        return linuxOperation;
    }
};


#endif // LINUXFACTORY

