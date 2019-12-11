#ifndef UDPWORKTHREAD_H
#define UDPWORKTHREAD_H
#include <QtNetwork>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "thread/threadsafequeue.h"
#include "modelfitting.h"
#include "workingthread.h"
class UdpWorkThread:public WorkingThread
{
    Q_OBJECT
public:
    UdpWorkThread(std::shared_ptr<MMSolver> solverPtr,std::shared_ptr<ThreadSafeQueue<MatF>> sendQueue,QObject *parent = nullptr);

    bool getPause() const;
    void setPause(bool value);

    bool getStarted() const;
    void setStarted(bool value);

private:
    std::shared_ptr<ThreadSafeQueue<MatF>> sendQueue;
    QUdpSocket mUdpSock;
    bool started;
    bool pause;
    int interval;
    bool first;
    bool hasShape;
    std::shared_ptr<MMSolver> solverPtr;

    void sendBroadcast();
    QVector<QHostAddress> getBroadcastAddressFromInterfaces();

    // QThread interface
protected:
    void run();
};

#endif // UDPWORKTHREAD_H
