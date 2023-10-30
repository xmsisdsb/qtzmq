#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "qzmqmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    /* 槽函数 ---- 实现控制发送和停止 */
    void on_sendOrStop_clicked();

private:
    Ui::Widget *ui;

    /* 通信管理 */
    QZmqManager * m_ZmqManage;

    /* 发送间隔定时器 */
    QTimer * m_Timer;
private:

    /* 初始化 */
    void init();
};
#endif // WIDGET_H
