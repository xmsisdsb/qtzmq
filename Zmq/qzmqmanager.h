#ifndef QZMQMANAGER_H
#define QZMQMANAGER_H

#include <QObject>
#include <QThread>
#include "qpublisher.h"
#include "qsubscriber.h"

class QZmqManager : public QObject
{
    Q_OBJECT
public:
    explicit QZmqManager(QObject *parent = nullptr);
    ~QZmqManager();

    /* 发送信息 --- 提供接口外部控制激活发送信号 */
    void sendData(const QByteArray data);

    /* 接收信息 --- 提供接口外部控制激活发送信号 */
    void recvData();

private:

    /* 发布者 */
    QPublisher * m_Pub;

    /* 订阅者 */
    QSubscriber * m_Sub;

    /* 发布者线程 */
    QThread * m_PubThread;

    /* 订阅者线程 */
    QThread * m_SubThread;

private:

    /* 初始化 */
    void init();

    /* 接收子线程返回的数据 */
    void showData(const QByteArray data);


signals:

    /* 发送信号 */
    void sig_send(const QByteArray data);

    /* 接收信号 */
    void sig_recv();

    /* 传递数据给界面 */
    void sig_showData(const QByteArray data);
};

#endif // QZMQMANAGER_H
