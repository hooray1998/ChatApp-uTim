#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <time.h>
#define ONE_SIZE 8000
#define DBG qDebug()<<__FILE__<<__FUNCTION__<<"():"<<__LINE__
//////////////////////////////////////////////////////////
/// \brief Widget::Widget
/// \param parent
///
/// 接下来需要写的：
/// 将udp都放到线程里，该文件下不再出现udp，服务器每个线程的port为 tcp的port*88，客户端的为66*port.   每个包发送后都要又反馈，确定发送成功，否则丢包严重。
///
///
///

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    srand(time(NULL));

    //避免一开始用户点击Send按钮，结果程序会无法正常运行
    cur = 0;
    pTcpServer = NULL;
    for(int i=0;i<MAX_USER;i++)
    {
        mythread[i] = NULL;
    }

    QDir dir;
    dir.setPath("serverRecv");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    filelist = dir.entryInfoList();

    //指定父对象，让其自动回收该区域的空间
    pTcpServer = new QTcpServer(this);

    //绑定当前网卡的所有IP，和监听的端口
    //pTcpServer->listen(QHostAddress::Any, 8888);

    //只要一建立连接成功，就会自动触发newConnection函数
    connect(pTcpServer, &QTcpServer::newConnection,
            [=]()
            {
                //取出建立好的连接套接字
                pTcpSocket = pTcpServer->nextPendingConnection();

                //获得客户端的IP和端口
                QString ip = pTcpSocket->peerAddress().toString();
                qint16 port = pTcpSocket->peerPort();
                QString temp = QString("[%1:%2]:The client connection is successful.").arg(ip).arg(port);

                ui->textEditRead->append(temp);

                //产生udpPort
                int uPort = rand()%88888;
                mythread[cur] = new MyThread(cur, pTcpSocket, uPort);
                mythread[cur]->start();


                //设置Udp端口号
                QString msg = QString("Udp_Init#%1").arg(uPort);
                mythread[cur]->WriteData(msg.toUtf8().data());

                DBG<<"udpPort is :"<<uPort;

                //-----------------------------------------------------------------------------------------------
                //接收到了内容之后，直接在显示区域显示消息
                /**/ connect(mythread[cur], SIGNAL(ReadData(int, QByteArray)),this,SLOT(analyzeData(int, QByteArray)));
                /**/ connect(mythread[cur], SIGNAL(RecvEnd()),this,SLOT(sendFileList()));
                //-----------------------------------------------------------------------------------------------
                cur++;
            }
            );

    connect(ui->ipLineEdit,SIGNAL(returnPressed()),this,SLOT(on_boundPushButton_clicked()));

    this->setWindowTitle("TcpServer");
    ui->textEditWrite->installEventFilter(this);

/////////////////////////////////////////////////////////
//加载样式表
    QFile file(":/other/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

}

Widget::~Widget()
{
    delete ui;
}

//给客户端发送消息的功能
void Widget::on_pushButtonSend_clicked()
{
    //获取编辑区域的内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发送消息,当有中文的时候就是用使用utf8

    str = "[Server:]" + ui->textEditWrite->toPlainText();
    ui->textEditRead->append(str); //在后面追加新的消息

    QString msg = QString("QunFa#%1#%2").arg(">>>Server<<<").arg(str);
    for(int i=0;i<cur;i++)
        mythread[i]->WriteData(msg.toUtf8().data());

    ui->textEditWrite->clear();
    ui->textEditWrite->setFocus();
}

//断开连接,拒绝接受来自客户端的消息
void Widget::on_pushButtonClose_clicked()
{
    //并告知所有用户下线，清空列表

}

bool Widget::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->textEditWrite)
    {
        if(event->type() == QEvent::KeyPress)//回车键
        {
             QKeyEvent *k = static_cast<QKeyEvent *>(event);
             if(k->key() == Qt::Key_Return)
             {
                 on_pushButtonSend_clicked();
                 return true;
             }
        }
    }
    return QWidget::eventFilter(target,event);
}

void Widget::analyzeData(int id, QByteArray array)
{
    QList<QByteArray>list = array.split('#');
    if(list.at(0)=="Login")
    {
        if(mythread[id]->getName()!=list.at(1))//新登陆
        {
            QString name = list.at(1);
            mythread[id]->setName(name);
            QString ip = mythread[id]->getIp();
            qint16 port = mythread[id]->getPort();
            QString temp = QString("[%1:%2]:The client is %3").arg(ip).arg(port).arg(name);
            ui->textEditRead->append(temp);

            //发送filelist
            int ss = filelist.size();
            QString msg2 = QString("FileList#%1#").arg(ss);
            for(int i=0;i<ss;i++)
            {
                msg2.append(filelist.at(i).fileName());
                msg2.append("$");
                msg2.append(QString::number(filelist.at(i).size()));
                msg2.append("$");
                msg2.append(QString::number(filelist.at(i).size()/ONE_SIZE+1));
                msg2.append("$");
            }

            mythread[id]->WriteData(msg2.toUtf8().data());

        }

        //更新列表
        for(int i=0;i<cur;i++)
        {
            if(i!=id)
                mythread[i]->WriteData(array);
        }
    }
    else if(list.at(0)=="Logout")
    {
        mythread[id]->die = true;
        QString name = list.at(1);
        QString ip = mythread[id]->getIp();
        qint16 port = mythread[id]->getPort();
        QString temp = QString("[%1:%2]:The client %3 下线").arg(ip).arg(port).arg(name);
        ui->textEditRead->append(temp);

        for(int i=0;i<cur;i++)
        {
            if(i!=id)
                mythread[i]->WriteData(array);
        }
    }
    else if(list.at(0)=="RequestFile")
    {
        QString filename = list.at(1);
        ui->textEditRead->append("正在发文件"+filename);
        mythread[id]->SendFile("serverRecv/"+filename);
    }
    else if(list.at(0)=="QunFa")
    {
        QString send = mythread[id]->getName();
        QString context = list.at(1);
        for(int i=0;i<cur;i++)
        {
            if(i!=id)
            {
                QString msg = QString("QunFa#%1#%2").arg(send).arg(context);
                mythread[i]->WriteData(msg.toUtf8().data());
            }
        }
    }
    else if(list.at(0)=="SiLiao")
    {
        QString send = mythread[id]->getName();
        QString answer = list.at(1);
        QString context = list.at(2);
        for(int i=0;i<cur;i++)
        {
            if(i!=id&&mythread[i]->getName()==answer)
            {
                QString msg = QString("SiLiao#%1#%2").arg(send).arg(context);
                mythread[i]->WriteData(msg.toUtf8().data());
            }
        }
    }
}

void Widget::on_boundPushButton_clicked()
{

    QString myAddr = ui->ipLineEdit->text();     //手动输入IP到edit框
    QString myPort = ui->portLineEdit->text();       //手动设置端口
    QString msg;
    bool ret = pTcpServer->listen(QHostAddress(myAddr),myPort.toUInt());      //服务器监听绑定
    if(!ret)
    {
        msg = "绑定失败";
    }
    else
    {
        msg = "绑定成功";
        //ui->boundPushButton->setEnabled(false);
    }

    ui->textEditRead->append(msg);
}

void Widget::sendFileList()
{

    //获得文件列表
    QDir dir("serverRecv");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    filelist = dir.entryInfoList();
    //发送filelist
    int ss = filelist.size();
    QString msg2 = QString("FileList#%1#").arg(ss);
    for(int i=0;i<ss;i++)
    {
        msg2.append(filelist.at(i).fileName());
        msg2.append("$");
        msg2.append(QString::number(filelist.at(i).size()));
        msg2.append("$");
        msg2.append(QString::number(filelist.at(i).size()/ONE_SIZE+1));
        msg2.append("$");
    }

    for(int i=0;i<cur;i++)
        mythread[i]->WriteData(msg2.toUtf8().data());
}
