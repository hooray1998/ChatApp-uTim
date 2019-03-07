#include "mythread.h"
#define DBG qDebug()<<__FILE__<<__FUNCTION__<<"():"<<__LINE__
#define ONE_SIZE 8000

MyThread::MyThread(int i, QTcpSocket *t,int uPort)
{
    die = false;
    id = i;
    tcpSocket = t;
    ip = t->peerAddress();
    qDebug()<<"ip:"<<ip;
    port = t->peerPort();
    receiving = false;

    udpPort = uPort;

//////////////////////////////////////////////这些要放到这，而不是run函数中，emmmmmmmm，调了一个小时.
    //udp接受文件
    i = 1;
    uSocket = new QUdpSocket;
    uSocket->bind(ip, 66*udpPort);
    DBG<<"bind :"<<ip.toString()<<"port:"<<66*udpPort;
//////////////////////////////////////////////
}

void MyThread::run()
{

    //-----------------------------------------------------------------------------------------------
    //接收到了内容之后，直接在显示区域显示消息
    /**/ connect(tcpSocket, &QTcpSocket::readyRead,
    /**/        [=]()
    /**/        {
    /**/           //从通信套接字中间取出内容
    /**/           QByteArray array = tcpSocket->readAll();
                   ReadData(id, array);
    /**/        }
    /**/        );
    //-----------------------------------------------------------------------------------------------

    connect(uSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

void MyThread::WriteData(QByteArray array)
{
    if(die) return ;
    tcpSocket->write(array);
    DBG<<" "<<ip<<"port:"<<port<<"   context:"<<array;
}

bool MyThread::equal(QTcpSocket *t)
{
    QString i = t->peerAddress().toString();
    qint16 p = t->peerPort();

    if(i==ip.toString()&&p==port)
        return true;
    else
        return false;
}

void MyThread::setName(QString n)
{
    name = n;
}

QString MyThread::getName()
{
    return name;
}

QString MyThread::getIp()
{
    return ip.toString();
}
qint16 MyThread::getPort()
{
    return port;
}

void MyThread::receive()
{

    //ui->textEditRead->append("receive");
    DBG<<"receive";

    QByteArray datagram;
    while(uSocket->hasPendingDatagrams())
    {
        datagram.resize(uSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        uSocket->readDatagram(datagram.data(), datagram.size(),
        &sender, &senderPort);

        if(datagram.indexOf("end#")!=-1)
        {
            DBG<<"end";
            receiving = false;
            file.close();
            emit RecvEnd();
        }
        else if(datagram.indexOf("start#")!=-1)
        {
            DBG<<"start";
            receiving = true;

            file.setFileName("serverRecv/"+datagram.split('#').at(1));
            if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
            {
                qDebug()<<"无法接收"<<endl;
                return ;
            }
            else
            {
                file.resize(0);
                i++;
                uSocket->writeDatagram("6",1, ip, 666*udpPort);
            }
        }
        else if(datagram=="6")
        {
            sendData();
        }
        else if(receiving)
        {

            file.write(datagram.data(),datagram.size());

            i++;
            uSocket->writeDatagram("6",1, ip, 666*udpPort);

            DBG<<"port:"<<senderPort<<" "<< i <<"=>"<< datagram.size();
        }

    }
}

void MyThread::SendFile(QString filename)
{
    DBG<<"start send file";

    file.setFileName(filename);
    DBG<<filename;
    i = 0;

    if (!file.open(QIODevice::ReadOnly))
    {
        DBG<<"打不开";
        return;
    }

    QStringList sp = filename.split("/");
        DBG<<"1";
    QString startmsg = QString("start#%1").arg(sp.at(sp.size()-1));
        DBG<<"2";
    uSocket->writeDatagram(startmsg.toUtf8().data() , ip,666*udpPort);
        DBG<<"3";
    DBG<<"send "<<startmsg<<"   to "<<666*udpPort;
}

void MyThread::sendData()
{
    if(!file.atEnd())
    {
        QByteArray line = file.read(ONE_SIZE);
        uSocket->writeDatagram( line , ip,666*udpPort);
        i++;
        qDebug() << "send over!" << i << line.size();
    }
    else
    {
        QString msg = QString("end#%1").arg(i);
        uSocket->writeDatagram( msg.toUtf8().data() , ip,666*udpPort);
    }
}
