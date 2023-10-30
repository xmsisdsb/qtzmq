/**
 * 修改历史
 * 创建文件   2023-10-27 xms
 */

/**
 * @file  QZmqManager.cpp
 * @brief
 *       功能：管理发布者和订阅者，由于只有一个程序，发送和接收是要同步进行的，
 *          本身只是单线程无法满足要求，因此采用多线程。
 */
#include "qzmqmanager.h"

QZmqManager::QZmqManager(QObject *parent) : QObject(parent)
{
    init();
}

QZmqManager::~QZmqManager()
{
    m_Sub->deleteLater();
    m_Pub->deleteLater();
    m_SubThread->deleteLater();
    m_PubThread->deleteLater();
}

/***
 * @date: 2023-10-27 16:47
 * @return:
 * @param:
 * @brief: 发送信息 --- 提供接口外部控制激活发送信号
 * @author: xms_HZX
 */
void QZmqManager::sendData(const QByteArray data)
{
    emit sig_send(data);
}

/***
 * @date: 2023-10-27 16:47
 * @return:
 * @param:
 * @brief: 接收信息 --- 提供接口外部控制激活发送信号
 * @author: xms_HZX
 */
void QZmqManager::recvData()
{
    emit sig_recv();
}

/***
 * @date: 2023-10-27 17:25
 * @return:
 * @param:
 * @brief: 初始化线程和发布订阅端
 * @author: xms_HZX
 */
void QZmqManager::init()
{
    //初始化发布端和线程，并将发布端移到线程
    m_Pub = new QPublisher;
    m_PubThread = new QThread;
    m_Pub->moveToThread(m_PubThread);
    connect(this, &QZmqManager::sig_send, m_Pub, &QPublisher::sendData);
    m_PubThread->start();


    //初始化订阅端和线程，并将订阅端移到线程
    m_Sub = new QSubscriber;
    m_SubThread = new QThread;
    m_Sub->moveToThread(m_SubThread);
    connect(this, &QZmqManager::sig_recv, m_Sub, &QSubscriber::recvData);
    connect(m_Sub, &QSubscriber::sig_show, this, &QZmqManager::showData);
    m_SubThread->start();
}

/***
 * @date: 2023-10-30 13:49
 * @return: 返回数据给界面 --- 界面显示
 * @param:  data数据界面显示
 * @brief:  接收子线程返回的数据
 * @author: xms_HZX
 */
void QZmqManager::showData(const QByteArray data)
{
    emit sig_showData(data);
}
