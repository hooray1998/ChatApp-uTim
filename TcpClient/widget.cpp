#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#define ONE_SIZE 8000
#define DBG qDebug()<<__FILE__<<__FUNCTION__<<"():"<<__LINE__
//////////////////////////////
////
/// 用户名居中显示
/// 自己的信息靠右显示
/// 服务器断开得有反应
///
/// 未读消息提醒
///
///
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //读取配置文件
    QFile *f_ip = new QFile("init_ip.txt");
    if(f_ip->open(QIODevice::ReadOnly))
    {
        ui->lineEdit->setText(f_ip->readAll());
        f_ip->close();
    }



    all_pianShu = 1;
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximumHeight(10);


    receiving = false;
    fileNum = 0;
    mode = -1;
    curChat = "讨论组";
    maxUserNum = 0;
    findOrCreate("讨论组");
    connected = false;
    connectTimer = new QTimer();
    connectTimer->start(5000);
    //connect(connectTimer,SIGNAL(timeout()),this,SLOT(on_pushButton_clicked()));
    connect(connectTimer,&QTimer::timeout,
    [=]()
    {

        if(connected)
        {
            QString msg = QString("Login#%1").arg(id);
            pTcpSocket->write(msg.toUtf8().data());
        }
        else
        {

            //获得服务器的IP和端口
            QString ip = ui->lineEdit->text();
            qint16 port = ui->lineEdit_2->text().toInt();

            //主动和服务器将建立连接
            pTcpSocket->connectToHost(QHostAddress(ip), port);
        }
    }

    );
    this->setWindowTitle("fakeTim");

    pTcpSocket = NULL;

    //分配空间，指定父对象
    pTcpSocket = new QTcpSocket(this);

    list = new QListView(ui->splitter_2);
    list->setBatchSize(70);

    list->setFont(QFont(NULL,25));
    list->setGridSize(QSize(100,50));
    model = new QStringListModel();
    userList<<"讨论组";
    model->setStringList(userList);
    list->setModel(model);
    list->setCurrentIndex(list->model()->index(0,0));


    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_connectPushButton_clicked()));

    //弹出来一个提示而已
    connect(pTcpSocket, &QTcpSocket::connected,
           [=]()
           {
               ui->connectPushButton->setText("已连接");
               ui->textEditRead->append("连接成功");
               connected = true;
               QString msg = QString("Login#%1").arg(id);
               pTcpSocket->write(msg.toUtf8().data());
           }
           );

    //显示来自服务器的消息
    connect(pTcpSocket, SIGNAL(readyRead()),this,SLOT(analyzeData()));

    on_connectPushButton_clicked();//开机连接
    ui->textEditWrite->installEventFilter(this);//按enter自动发送
    connect(list,SIGNAL(clicked(QModelIndex)),this,SLOT(chatWith(QModelIndex)));
    setStyleSheet("background-image:url(:/other/image/5.jpg)");


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

/////////////////////////////////////////////////////////
}

Widget::~Widget()
{
    delete ui;
}


//与服务器建立连接
void Widget::on_connectPushButton_clicked()
{
        if(connected)
        {
            qDebug()<<"请求断开。。。。。。。";
            userList.clear();
            userList<<"讨论组";
            model->setStringList(userList);

            QString msg = QString("Logout#%1").arg(id);
            pTcpSocket->write(msg.toUtf8().data());

            ui->connectPushButton->setText("未连接");
            connected = false;

            pTcpSocket->disconnectFromHost();
            ui->textEditRead->append("断开连接");
        }
        else
        {

            //获得服务器的IP和端口
            QString ip = ui->lineEdit->text();
            qint16 port = ui->lineEdit_2->text().toInt();

            //主动和服务器将建立连接
            pTcpSocket->connectToHost(QHostAddress(ip), port);
        }
}


//给服务器发送消息
void Widget::on_pushButton_2_clicked()
{
    ui->progressBar->show();
    if(!connected) return ;//连接成功才能发送
    if(curChat=="讨论组")
    {
        QString msg = QString("QunFa#%1").arg(ui->textEditWrite->toPlainText());
        pTcpSocket->write(msg.toUtf8().data());
    }
    else
    {
        //获取编辑区域的内容
        QString str = QString("SiLiao#%1#%2").arg(curChat).arg(ui->textEditWrite->toPlainText());
        //给对方发送消息,当有中文的时候就是用使用utf8
        pTcpSocket->write(str.toUtf8().data());
    }

    QString str = "[Me]: " + ui->textEditWrite->toPlainText();
    //ui->textEditRead->append(str); //在后面追加新的消息
    recordMsg(curChat, str);
    showMsg();

    ui->textEditWrite->clear();
    ui->textEditWrite->setFocus();
}


//断开连接
void Widget::on_pushButton_3_clicked()
{
    userList.clear();
    userList<<"讨论组";
    model->setStringList(userList);

    QString msg = QString("Logout#%1").arg(id);
    pTcpSocket->write(msg.toUtf8().data());

   ui->connectPushButton->setText("未连接");
   connected = false;

    pTcpSocket->disconnectFromHost();
    ui->textEditRead->append("断开连接");

    this->close();
}
bool Widget::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->textEditWrite)
    {
        if(event->type() == QEvent::KeyPress)
        {
             QKeyEvent *k = static_cast<QKeyEvent *>(event);
             if (k->key() == Qt::Key_Return )
             {
                 on_pushButton_2_clicked();
                 return true;
             }
             else if (k->key() == Qt::Key_Tab && (k->modifiers() & Qt::ControlModifier))
             {
                 changeChatWith();
             }
        }
    }
    return QWidget::eventFilter(target,event);
}

void Widget::showLoginWidget()
{
    loginWidget = new QWidget();
    loginWidget->resize(QSize(400,300));

    QLineEdit *name = new QLineEdit(loginWidget);
    name->setMaxLength(3);
    name->setPlaceholderText("用户名");
    name->setFont(QFont(NULL,25));
    QLineEdit *secret = new QLineEdit(loginWidget);
    secret->setEchoMode(QLineEdit::Password);
    secret->setAttribute(Qt::WA_InputMethodEnabled, false);//屏蔽中文输入法
    secret->setPlaceholderText("密码");
    secret->setFont(QFont(NULL,25));
    QPushButton *loginButton = new QPushButton(loginWidget);
    loginButton->setText("登录");
    loginButton->setFont(QFont(NULL,25));

    name->setGeometry(50,50,300,50);
    secret->setGeometry(50,150,300,50);
    loginButton->setGeometry(120,220,160,50);

    loginWidget->show();

    connect(secret,&QLineEdit::returnPressed,
            [=]()
           {
                id = name->text();
                this->show();
                ui->textEditWrite->setFocus();
                ui->nameLabel->setText("  "+id);
                loginWidget->close();
                QString msg = QString("Login#%1").arg(id);
                pTcpSocket->write(msg.toUtf8().data());
           }
           );
    connect(loginButton, &QPushButton::clicked,
            [=]()
           {
                id = name->text();
                this->show();
                ui->textEditWrite->setFocus();
                ui->nameLabel->setText("  "+id);
                loginWidget->close();
                QString msg = QString("Login#%1").arg(id);
                pTcpSocket->write(msg.toUtf8().data());
           }
           );
}

void Widget::chatWith(QModelIndex index)
{
    curChat = model->data(index).toByteArray();
    ui->chatNameLabel->setText(curChat);

    showMsg();
}

void Widget::addUser(QString user)
{
    if(user.isEmpty()) return ;
    if(userList.indexOf(user)==-1)
    {
        userList<<user;
        model->setStringList(userList);

        findOrCreate(user);
    }
}
void Widget::delUser(QString user)
{
    int find = userList.indexOf(user);
    if(find>0)
    {
        userList.removeAt(find);
        model->setStringList(userList);

        find = findOrCreate(user);
        record[find]->msgList.clear();
        record[find]->die = true;
    }
}

void Widget::analyzeData()
{
       //从通信套接字中间取出内容

        QList<QByteArray> list = pTcpSocket->readAll().split('#');
        QString msg;

        if(list.at(0)=="Logout")//-1
        {
            delUser(list.at(1));
        }
        else if(list.at(0)=="Udp_Init")//4
        {
            qint16 pp = list.at(1).toInt();
            udpPort = pp;
            DBG<<"udp Port is "<<udpPort;
            initUdpSocket();
        }
        else if(list.at(0)=="Login")//0
        {
            addUser(list.at(1));
        }
        else if(list.at(0)=="QunFa")
        {
            QString send = list.at(1);
            QString context = list.at(2);
            msg = QString("[%1]: %2").arg(send).arg(context);
            //ui->textEditRead->append(msg); //在后面追加新的消息
            recordMsg("讨论组", msg);
            changeChatWith(0);
        showMsg();
        }
        else if(list.at(0)=="SiLiao")
        {
            QString send = list.at(1);
            QString context = list.at(2);
            msg = QString("[%1]: %2").arg(send).arg(context);
            //ui->textEditRead->append(msg); //在后面追加新的消息
            recordMsg(send, msg);
            int find = userList.indexOf(send);
            if(find!=-1)
                changeChatWith(find);
        showMsg();
        }
        else if(list.at(0)=="FileList")
        {
            DBG<<"FileList";
            int ss = list.at(1).toInt();
            DBG<<"Size :"<<ss;
            if(ss>0)
            {
                QList<QByteArray> list2 = list.at(2).split('$');
                int sss = list2.size()-1;
                DBG<<"file sss*3:"<<sss;
                fileNum = 0;
                for(int i=0;i<sss;i+=3,fileNum++)
                {
                    DBG<<list2.at(i);
                    fileinfo[fileNum].filename = list2.at(i);
                    fileinfo[fileNum].filesize = list2.at(i+1);
                    fileinfo[fileNum].sizecount = list2.at(i+2);
                }
            }

        }
}


void Widget::changeChatWith(int cur)
{
    QModelIndex curindex = list->currentIndex();

    if(cur==-1)
    {
        //切换列表
        if(curindex.row()<list->model()->rowCount()-1)
            list->setCurrentIndex(list->model()->index(curindex.row()+1,0));
        else
            list->setCurrentIndex(list->model()->index(0,0));

    }
    else
    {
        list->setCurrentIndex(list->model()->index(cur,0));

    }


    curChat = model->data(list->currentIndex()).toByteArray();
    ui->chatNameLabel->setText(curChat);

    showMsg();
}

void Widget::showMsg()
{
    ui->textEditRead->clear();
    int find = findOrCreate(curChat);
    for(int i=0;i<record[find]->msgList.size();i++)
    {
        ui->textEditRead->append(record[find]->msgList.at(i));
    }
}

int Widget::findOrCreate(QString na)
{
    int firstDieUser=maxUserNum;
    for(int i=0;i<maxUserNum;i++)
    {
        if(record[i]->name==na&&record[i]->die==false)
        {
            return i;
        }
        else if(firstDieUser==maxUserNum&&record[i]->die==true)
        {
            firstDieUser = i;
        }
    }
    if(maxUserNum==firstDieUser)
        maxUserNum++;
    record[firstDieUser] = new Record();
    record[firstDieUser]->die = false;
    record[firstDieUser]->name = na;
    return firstDieUser;
}

void Widget::recordMsg(QString send, QString msg)
{
    int find = findOrCreate(send);
    record[find]->msgList.append(msg);
    /*
    if(curChat!=send)
    {
        record[find]->isread = false;

        find = userList.indexOf(user);
        if(find>0)
        {
            model->setStringList(userList);

            find = findOrCreate(user);
            record[find]->msgList.clear();
            record[find]->die = true;
        }
    }
    */
}

void Widget::test()
{
    this->show();
    id = QString("id%1").arg(rand()%100);
    ui->textEditWrite->setFocus();
    ui->nameLabel->setText("  "+id);
}

void Widget::on_sendFilePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"选择发送的文件",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

    file.setFileName(fileName);
    QFileInfo qFileinfo;
    qFileinfo.setFile(fileName);
    all_pianShu = qFileinfo.size()/ONE_SIZE+1;
    DBG<<"size is "<<qFileinfo.size()<<"---总片数为:"<<all_pianShu;

    DBG<<fileName;
    i = 0;

    if (!file.open(QIODevice::ReadOnly))
    {
        DBG<<"打不开";
        return;
    }

    QStringList sp = fileName.split("/");
    QString startmsg = QString("start#%1").arg(sp.at(sp.size()-1));
    DBG<<pTcpSocket->peerAddress()<<"----"<<66*udpPort;
    udpSocket->writeDatagram( startmsg.toUtf8().data() , pTcpSocket->peerAddress(),66*udpPort);
    DBG<<"send "<<startmsg<<"   to "<<66*udpPort;
}

void Widget::sendData()
{
    if(!file.atEnd())
    {
        QByteArray line = file.read(ONE_SIZE);
        udpSocket->writeDatagram( line , pTcpSocket->peerAddress(),66*udpPort);
        i++;
        ui->progressBar->setValue(100*i/all_pianShu);
        qDebug() << "send over!" << i << line.size();
    }
    else
    {
        QString msg = QString("end#%1").arg(i);
        udpSocket->writeDatagram( msg.toUtf8().data() , pTcpSocket->peerAddress(),66*udpPort);
    }
}

void Widget::initUdpSocket()
{
    i = 0;
    udpSocket = new QUdpSocket(this);
    DBG<<"bind:"<<pTcpSocket->peerAddress()<<"---"<<666*udpPort;
    udpSocket->bind(pTcpSocket->peerAddress(),666*udpPort);

    connect(udpSocket, SIGNAL(readyRead()),
    this, SLOT(readPendingDatagrams()));
}

void Widget::readPendingDatagrams()
{
    //receive
    DBG<<"receive";
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams())
    {
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
        &sender, &senderPort);

        if(datagram.indexOf("end#")!=-1)
        {
            DBG<<"end";
            receiving = false;
            file.close();
        }
        else if(datagram.indexOf("start#")!=-1)
        {
            DBG<<"start";
            receiving = true;

            file.setFileName("timRecv/"+datagram.split('#').at(1));
            i = 0;
            if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
            {
                qDebug()<<"无法接收"<<endl;
                return ;
            }
            else
            {
                file.resize(0);
                i++;
                ui->progressBar->setValue(100*i/all_pianShu);
                udpSocket->writeDatagram("6",1, pTcpSocket->peerAddress(), 66*udpPort);
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
            ui->progressBar->setValue(100*i/all_pianShu);
            udpSocket->writeDatagram("6",1, pTcpSocket->peerAddress(), 66*udpPort);

            DBG<<"port:"<<senderPort<<" "<< i <<"=>"<< datagram.size();
        }
    }
}

void Widget::on_acceptFilePushButton_clicked()
{

    fileWidget = new QTableWidget();
    fileWidget->resize(QSize(670,500));
    fileWidget->setColumnCount(4);

    QStringList headers;
    headers<<"名称"<<"类型"<<"大小"<<"片数";
    fileWidget->setHorizontalHeaderLabels(headers);
    fileWidget->horizontalHeader()->resizeSection(0,300);


    //设置内容
    for(int i=0;i<fileNum;i++)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        fileWidget->insertRow(i);
        item0->setText(fileinfo[i].filename);

        //类型
        int s3 = fileinfo[i].filename.split('.').size();
        QString  type;
        if(s3>1)
            type = QString("%1 File").arg(fileinfo[i].filename.split('.').at(s3-1));
        else
            type = QString("未知文件");

        item1->setText(type);
        item2->setText(fileinfo[i].filesize);
        item3->setText(fileinfo[i].sizecount);
        fileWidget->setItem(i,0,item0);
        fileWidget->setItem(i,1,item1);
        fileWidget->setItem(i,2,item2);
        fileWidget->setItem(i,3,item3);
    }

    connect(fileWidget,&QTableWidget::doubleClicked,
            [=](){

                int curitem = fileWidget->currentRow();
                all_pianShu = fileinfo[curitem].sizecount.toInt();
                QString msg = QString("RequestFile#%1").arg(fileinfo[curitem].filename);
                pTcpSocket->write(msg.toUtf8().data());
                fileWidget->close();

            });

    fileWidget->setStyleSheet("selection-background-color:red");
    fileWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    fileWidget->show();

}

void Widget::closeEvent(QCloseEvent *e)
{
    on_pushButton_3_clicked();
    e->accept();
}
