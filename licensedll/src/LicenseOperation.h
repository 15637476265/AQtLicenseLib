#ifndef LICENSEOPERATION_H
#define LICENSEOPERATION_H

#include <QObject>
#include "licenseCreat.h"
#include "licenseread.h"
#include "LicenseCheck.h"
#include <QSettings>
#include <QUdpSocket>
#include <QDateTime>
#include <QProcess>
#include <QCoreApplication>

class LicenseOperation : public QObject
{
    Q_OBJECT
public:
    explicit LicenseOperation(QObject *parent = nullptr);

    QString getCurrentTime(bool system);
    QString getProcessorID();
    bool    getStartStatus();
    void    writeLicense(QString license,QString path,QString fileName);


    bool    startProcess();

    void    initLicense(int days);

    void    printAbout();

    int     getLicenseDays();



private:
    void     initPathAndFilename();
    void     initNtpServer();
    QString  getRegisterTime();
    bool     getSurplusDays(int days);
    bool     checkLicense();
    bool     daysSpacing(QString arg1,QString arg2,int days);
    QString  formatString(QString data);
signals:

protected slots:
    void readProcess();
    void processFinished();
    void udp_receive();

    void connectsucess();

private:
    QString  currentLicense;
    QString  systemLicense;
    QString  license_path;
    QString  license_fileName;
    QSettings settings;
    QUdpSocket *udpSocket;

    QString ntpHost;
    QProcess *mProcess;

private:
    QString processID;

private:
    bool netValid;
    QDateTime current_Time;
    QString registerTime;
    QString Ntp_Time;
    int    licenseDays;
    int    validLicenseDays;
};

#endif // LICENSEOPERATION_H
