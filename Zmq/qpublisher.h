#ifndef QPUBLISHER_H
#define QPUBLISHER_H

#include <QObject>
#include <QDebug>
#include "zmq.h"

class QPublisher : public QObject
{
    Q_OBJECT
public:
    explicit QPublisher(QObject *parent = nullptr);
    ~QPublisher();

    /* 发送数据 */
    void sendData(const QByteArray data);

private:

    /* 上下文 */
    void * m_Context;

    /* 发布者 */
    void * m_Publisher;

private:
    /* 发布者初始化 */
    void pubInit();

signals:

};

#endif // QPUBLISHER_H
