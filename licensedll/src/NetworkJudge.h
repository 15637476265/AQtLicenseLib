#ifndef NETWORKJUDGE_H
#define NETWORKJUDGE_H

#include <QHostInfo>
#include <QNetworkConfigurationManager>
#include <QProcess>

class NetworkJudge: public QObject
{
    Q_OBJECT
public:
    NetworkJudge();
    void startJudgeInternet();
    bool judgeNetIsValid();

    bool judgeInternet();
    void onlineStateChanged(bool isOnline);
protected slots:
    void onLookupHost(const QHostInfo &host);
    void readProcess();
private:
    bool linking;
    QProcess *mProcess;
};

#endif // NETWORKJUDGE_H
