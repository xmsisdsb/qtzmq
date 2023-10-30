/**
 * 修改历史
 * 创建文件 2023-10-27 XMS
 */

/**
 * @file  QPublisher.cpp
 * @brief
 *       功能：发布者 相当于服务器，往外发送信息
 *
 */

#include "qpublisher.h"

QPublisher::QPublisher(QObject *parent) : QObject(parent)
{
    pubInit();
}

QPublisher::~QPublisher()
{
    //关闭订阅者
    zmq_close(m_Publisher);

    //释放上下文
    zmq_ctx_destroy(m_Context);
}

/***
 * @date: 2023-10-27 16:30
 * @return:
 * @param:
 * @brief: 发布者初始化
 * @author: xms_HZX
 */
void QPublisher::pubInit()
{
    //创建zmq pub上下文
    m_Context = zmq_ctx_new();

    //创建zmq发布者
    m_Publisher = zmq_socket(m_Context, ZMQ_PUB);

    //绑定端口
    zmq_bind(m_Publisher, "tcp://*:9999");
}

/***
 * @date: 2023-10-27 16:39
 * @return:
 * @param: data 本次需要发送的数据
 * @brief: 发送数据
 * @author: xms_HZX
 */
void QPublisher::sendData(const QByteArray data)
{
    zmq_send(m_Publisher, data.data(), data.size(), 0);
}
