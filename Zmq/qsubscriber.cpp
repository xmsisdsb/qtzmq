/**
 * 修改历史
 * 创建文件 2023-10-27 XMS
 */

/**
 * @file  QSubscriber.cpp
 * @brief
 *       功能：订阅者 相当于客户端，接收信息
 *
 */

#include "qsubscriber.h"

QSubscriber::QSubscriber(QObject *parent) : QObject(parent)
{
    subInit();
}

QSubscriber::~QSubscriber()
{
    //关闭订阅者
    zmq_close(m_Subscriber);

    //释放上下文
    zmq_ctx_destroy(m_Context);
}

/***
 * @date: 2023-10-27 16:30
 * @return:
 * @param:
 * @brief: 订阅者初始化
 * @author: xms_HZX
 */
void QSubscriber::subInit()
{
    //创建zmq pub上下文
    m_Context = zmq_ctx_new();

    //创建zmq发布者
    m_Subscriber = zmq_socket(m_Context, ZMQ_SUB);

    //绑定端口
    zmq_connect(m_Subscriber, "tcp://localhost:9999");

    zmq_setsockopt(m_Subscriber, ZMQ_SUBSCRIBE, nullptr, 0);
}

/***
 * @date: 2023-10-27 16:39
 * @return:
 * @param:
 * @brief: 接收数据
 * @author: xms_HZX
 */
void QSubscriber::recvData()
{
    while(1)
    {
        char buf[256];
        memset(buf, 0, sizeof(char) * 256);
        int len = zmq_recv(m_Subscriber, buf, 256, 0);
        QByteArray ba(buf, strlen(buf));
        qDebug() << len;
        if(len > 0)
            emit sig_show(ba);
    }
}
