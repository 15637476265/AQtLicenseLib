#include "widget.h"
#include "ui_widget.h"
#include "cpuinfo.h"
#include <QProcess>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("CSDN IT1995");

    m_catProcess = new QProcess;
    connect(m_catProcess, SIGNAL(readyRead()), this, SLOT(readProcess()));
    connect(m_catProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished()));
    catShellCalled();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setLicenseDays(int days)
{
    QString data = "Valid Days:"+QString::number(days);
    ui->license->setText(data);
}

void Widget::catShellCalled()
{
    QString cmdCat = CPUInfo::getCommand();
    m_catProcess->start(cmdCat);
}

void Widget::readProcess()
{
    QString allMsg = m_catProcess->readAll();
    QStringList list = allMsg.split("\n");
    for(int i = 0; i < list.size(); i++){
        m_msgVec << list[i];
    }
}

void Widget::processFinished()
{
    qDebug()<< "processFinished() called";
    QString cpuInfo = CPUInfo::getCPUInformation(m_msgVec);
    ui->label->setText(cpuInfo);
}
