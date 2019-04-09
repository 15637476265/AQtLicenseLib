#include "NetworkJudge.h"



NetworkJudge::NetworkJudge()
{
    linking = false;
    mProcess = new QProcess(this);
    connect(mProcess, SIGNAL(readyRead()), this, SLOT(readProcess()));
}

void NetworkJudge::startJudgeInternet()
{
    qDebug() << "开始执行网络验证！";
    qDebug() << "1.网络连接验证:"  << judgeNetIsValid();
    qDebug() << "2.Host连接验证:" << judgeInternet();
    qDebug() << "验证完成!";
}

bool NetworkJudge::judgeNetIsValid()
{
    QNetworkConfigurationManager net;
    return  net.isOnline();
}

bool NetworkJudge::judgeInternet()
{
    //QHostInfo::lookupHost("www.baidu.com",this,SLOT(onLookupHost(QHostInfo)));
    mProcess->start("ping pool.sntp.org");
    mProcess->waitForFinished();
    return  linking;
}

void NetworkJudge::onLookupHost(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "网络未连接!";
        qDebug() << "失败原因:" << host.errorString();
        linking = false;
    }
    else{
        qDebug() << "网络已连接!";
        linking = true;
    }

}

void NetworkJudge::readProcess()
{
    linking = mProcess->readAll().trimmed().contains("TTL=");
}
