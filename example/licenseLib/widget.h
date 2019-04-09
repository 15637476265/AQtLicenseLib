#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

QT_BEGIN_NAMESPACE
class QProcess;
QT_END_NAMESPACE

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setLicenseDays(int days);

protected:
    void catShellCalled();

protected slots:
    void readProcess();
    void processFinished();

private:
    Ui::Widget *ui;
    QProcess *m_catProcess;
    QVector<QString> m_msgVec;
};

#endif // WIDGET_H
