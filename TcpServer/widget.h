#ifndef WIDGET_H
#define WIDGET_H
#define MAX_USER 100

#include <QWidget>
#include <QTcpServer>  //监听套接字
#include <QNetworkInterface>
#include <QTcpSocket>  //通信套接字
#include <QUdpSocket>
#include <QKeyEvent>
#include <QDebug>
#include <QSet>
#include <QFile>
#include <QFileInfoList>
#include <QDir>

#include "mythread.h"



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();
    void analyzeData(int id, QByteArray array);
    void on_boundPushButton_clicked();

    void sendFileList();
    //void receive();
protected:

    bool eventFilter(QObject *target, QEvent *event);

private:
    Ui::Widget *ui;

    QTcpServer *pTcpServer;
    QTcpSocket *pTcpSocket;
    MyThread *mythread[MAX_USER];
    QSet<QString> userSet;
    int cur;

    QUdpSocket *uSocket;

    QFileInfoList filelist;
};

#endif // WIDGET_H
