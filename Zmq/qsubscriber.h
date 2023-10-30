#ifndef QSUBCRIBER_H
#define QSUBCRIBER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "zmq.h"

class QSubscriber : public QObject
{
    Q_OBJECT
public:
    explicit QSubscriber(QObject *parent = nullptr);
    ~QSubscriber();

    /* 接收数据 */
    void recvData();

private:

    /* 上下文 */
    void * m_Context;

    /* 订阅者 */
    void * m_Subscriber;

private:
    /* 订阅者初始化 */
    void subInit();

signals:

    /* 收到数据提示界面显示 */
    void sig_show(const QByteArray data);
};

#endif // QSUBCRIBER_H
