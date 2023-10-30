/**
 * 修改历史
 * 创建文件 2023-10-27 XMS
 */

/**
 * @file  Widget.cpp
 * @brief
 *       功能：实现界面功能，点击发送、停止，消息在界面上显示，通过zmqmanage控制发布订阅
 *       发送数据为当前时间，定时器控制发送间隔
 */

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

Widget::~Widget()
{
    delete ui;
    m_ZmqManage->deleteLater();
}

/***
 * @date: 2023-10-27 17:44
 * @return:
 * @param:
 * @brief: 槽函数 ---- 实现控制发送和停止
 * @author: xms_HZX
 */
void Widget::on_sendOrStop_clicked()
{
    QPushButton * pb = qobject_cast<QPushButton * > (sender());
    if(pb->text() == "开始发送")
    {
        pb->setText("停止发送");
        m_Timer->start(500);
    }
    else if(pb->text() == "停止发送")
    {
        pb->setText("开始发送");
        m_Timer->stop();
    }
}

/***
 * @date: 2023-10-27 17:51
 * @return:
 * @param:
 * @brief: 初始化
 * @author: xms_HZX
 */
void Widget::init()
{
    m_ZmqManage = new QZmqManager;
    m_ZmqManage->recvData();
    connect(m_ZmqManage, &QZmqManager::sig_showData, this, [&](const QByteArray data){
        ui->textEdit_Recv->append(QString(data));
    });
    m_Timer = new QTimer(this);
    connect(m_Timer, &QTimer::timeout, this, [&](){
            QString data = "当前时间为：" + QDateTime::currentDateTime().toString("yyyyMMdd:hhmmss");
            ui->textEdit_Send->append("我发的数据----" + data);
            QByteArray ba(QString("我收到的数据---%1").arg(data).toUtf8());
            m_ZmqManage->sendData(ba);
    });
}
