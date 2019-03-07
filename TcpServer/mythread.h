#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QTcpSocket>  //通信套接字
#include <QHostAddress>

#include <QSetIterator>
#include <QObject>
#include <QThread>
#include <QtDebug>
#include <QWidget>
#include <QByteArray>
#include <QUdpSocket>
#include <QFile>



class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(int i, QTcpSocket *t,int uPort);
    void WriteData(QByteArray);
    bool equal(QTcpSocket*t);
    QString getIp();
    qint16 getPort();

    void setName(QString n);
    QString getName();
    bool die;
public slots:
    void receive();
    void SendFile(QString filename);
    void sendData();

signals:
    ReadData(int, QByteArray);
    void RecvEnd();
protected:
    void run();
private:
    QTcpSocket *tcpSocket;
    QHostAddress ip;
    qint16 port;
    int id;
    QString name;

    QUdpSocket *uSocket;
    int udpPort;
    int i;
    QFile file;
    bool receiving;
};

#endif // MYTHREAD_H
