#include "LicenseOperation.h"
#include <QDebug>
#include "NetworkJudge.h"


LicenseOperation::LicenseOperation(QObject *parent) : QObject(parent)
{

}

#if 0
QString LicenseOperation::getCurrentTime(bool system)
{
    if(!system){
        return QDateTime::currentDateTime().toString("yyyyMMdd");
    }else{
        QString net_time;
        QByteArray netClock;
        socket->connectToHost(ntpHost,123);
        if(socket->waitForConnected(3000)){
            qDebug()<<"Net Clock1----->"<<netClock;
            if(socket->waitForReadyRead()){
                net_time = socket->readAll();
                qDebug()<<"Net Clock2----->"<<net_time;
                net_time = net_time.trimmed();
                net_time = net_time.section("",1,2);
            }
        }else {
            qDebug()<<"errorString----->"<<socket->errorString();
            net_time = "20190407";
        }
        socket->close();
        delete socket;
        //qDebug()<<"Net Clock----->"<<net_time;
        return net_time;
    }
}
#else
QString LicenseOperation::getCurrentTime(bool system)
{
    if(!system){
        return QDateTime::currentDateTime().toString("yyyyMMdd");
    }else{
        QByteArray netClock;
        udpSocket->connectToHost(ntpHost,123);
        if(udpSocket->waitForConnected(3000)){
            if(udpSocket->waitForReadyRead()){

            }
        }else {
            qDebug()<<"errorString----->"<<udpSocket->errorString();
            Ntp_Time = QDateTime::currentDateTime().toString("yyyyMMdd");
        }
        udpSocket->disconnectFromHost();
        udpSocket->close();
        delete udpSocket;
        return Ntp_Time;
    }
}
#endif


QString LicenseOperation::getProcessorID()
{
    QString cmd;
    #ifdef Q_OS_WIN
        cmd = "wmic cpu get processorID";
    #else
        cmd = "cat /proc/cpuinfo";
    #endif
    mProcess->start(cmd);
    mProcess->waitForFinished();
    return processID;
}

bool LicenseOperation::getStartStatus()
{
    bool status = settings.value("status").toBool();
    if(!status){
        current_Time = QDateTime::currentDateTime();
        settings.setValue("status",true);
        settings.setValue("time",current_Time.toString("yyyyMMdd"));
        return true;
    }
    return false;
}

bool LicenseOperation::checkLicense()
{
    systemLicense = LicenseRead::readFileLicense(license_path,license_fileName);
    if(systemLicense == "N") return false;
    return LicenseCheck::licenseCheck(currentLicense,systemLicense);
}

bool LicenseOperation::startProcess()
{
    QString result;
    if(getStartStatus()){
        result = "001";
        currentLicense = LicenseCreat::creatLicenseStr(getProcessorID(),result);
        LicenseCreat::creatLicenseFile(license_path,license_fileName,currentLicense);
    }

    getSurplusDays(licenseDays) ? result = "001" : result = "002";

    currentLicense = LicenseCreat::creatLicenseStr(getProcessorID(),result);
    return checkLicense();
}

void LicenseOperation::initLicense(int days)
{
    NetworkJudge net;
    netValid = net.judgeInternet();
    licenseDays = days;
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(udp_receive()));
    connect(udpSocket, SIGNAL(connected()), this, SLOT(connectsucess()));
    mProcess =  new QProcess;
    connect(mProcess, SIGNAL(readyRead()), this, SLOT(readProcess()));
    connect(mProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished()));
    this->initPathAndFilename();
    initNtpServer();
}

void LicenseOperation::printAbout()
{
    qDebug()<<"License Valid----->"<<validLicenseDays;
    qDebug()<<"License Regisiter Day----->"<<registerTime;
}

int LicenseOperation::getLicenseDays()
{
    return validLicenseDays;
}

bool LicenseOperation::getSurplusDays(int days)
{
    registerTime = getRegisterTime();
    if(netValid){
        Ntp_Time = getCurrentTime(netValid);
        return daysSpacing(Ntp_Time,registerTime,days);
    }else{
        return daysSpacing(current_Time.toString("yyyyMMdd"),registerTime,days);
    }
}

bool LicenseOperation::daysSpacing(QString arg1, QString arg2 ,int days)
{
    QDateTime start,end;
    end = QDateTime::fromString(arg1,"yyyyMMdd");
    start = QDateTime::fromString(arg2,"yyyyMMdd");
    validLicenseDays = start.daysTo(end); //求时间差;
    if(days > validLicenseDays){
        validLicenseDays = days - validLicenseDays;
        return true;
    }else{
        validLicenseDays = 0;
        return false;
    }
}

void LicenseOperation::initPathAndFilename()
{
    license_fileName = "license.dat";
    qDebug()<<QCoreApplication::applicationDirPath()+"/license/";
    license_path = QCoreApplication::applicationDirPath()+"/license/";
}

void LicenseOperation::initNtpServer()
{
    //ntpHost = "pool.sntp.org";

    //ntpHost = "202.120.2.101";
    //ntpHost = "159.226.154.47";
    //ntpHost = "0.cn.pool.ntp.org"
//    ntpHost = "ntp.sjtu.edu.cn";

//    ntpHost = "ntp1.aliyun.com";
//    ntpHost = "time.windows.com";
    ntpHost = "ntp4.aliyun.com";


}

QString LicenseOperation::getRegisterTime()
{
    return settings.value("time").toString();
}

void LicenseOperation::readProcess()
{
    processID = mProcess->readAll().trimmed().remove(0,21);
}

void LicenseOperation::processFinished()
{
    //qDebug()<< "processFinished() called";
}


void LicenseOperation::udp_receive()
{
    QByteArray newTime;
    QDateTime Epoch(QDate(1900, 1, 1));
    QDateTime unixStart(QDate(1970, 1, 1));

    while(udpSocket->hasPendingDatagrams())
    {
        newTime.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(newTime.data(),newTime.size());
    }

    QByteArray TransmitTimeStamp ;
    TransmitTimeStamp=newTime.right(8);
    quint32 seconds=TransmitTimeStamp[0];
    quint8 temp=0;
    for(int j=1;j<=3;j++)
    {
        seconds=seconds<<8;
        temp=TransmitTimeStamp.at(j);
        seconds=seconds+temp;
    }
    QDateTime time;
    time.setTime_t(seconds-Epoch.secsTo(unixStart));

    QStringList timeList = time.toString().split(" ");
    QString _moon = timeList.at(1);
    _moon = _moon.left(_moon.length() - 1);
    _moon = formatString(_moon);
    QString days = timeList.at(2);
    days = formatString(days);
    QString year = timeList.last();

    Ntp_Time = year+_moon+days;
    qDebug()<<"Net Clock----->"<<Ntp_Time;

}

QString LicenseOperation::formatString(QString data){
    return (10>data.toInt())?(data="0"+data):data;
}



void LicenseOperation::connectsucess()
{
    qint8 LI=0;
    qint8 VN=3;
    qint8 MODE=3;
    qint8 STRATUM=0;
    qint8 POLL=4;
    qint8 PREC=-6;
    QDateTime Epoch(QDate(1900, 1, 1));
    qint32 second=quint32(Epoch.secsTo(QDateTime::currentDateTime()));
    qint32 temp=0;
    QByteArray timeRequest(48, 0);
    timeRequest[0]=(LI <<6) | (VN <<3) | (MODE);
    timeRequest[1]=STRATUM;
    timeRequest[2]=POLL;
    timeRequest[3]=PREC & 0xff;
    timeRequest[5]=1;
    timeRequest[9]=1;
    timeRequest[40]=(temp=(second&0xff000000)>>24);
    temp=0;
    timeRequest[41]=(temp=(second&0x00ff0000)>>16);
    temp=0;
    timeRequest[42]=(temp=(second&0x0000ff00)>>8);
    temp=0;
    timeRequest[43]=((second&0x000000ff));
    udpSocket->flush();
    udpSocket->write(timeRequest);
    udpSocket->flush();
}
