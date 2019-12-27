#ifndef UDPWORKTHREAD_H
#define UDPWORKTHREAD_H
#include <QtNetwork>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "thread/threadsafequeue.h"
#include "modelfitting.h"
#include "workingthread.h"
#include "src/MMSolver.h"
class UdpWorkThread:public WorkingThread
{
    Q_OBJECT
public:
    UdpWorkThread(std::shared_ptr<MMSolver> solverPtr,std::shared_ptr<MMSolver> g8mSolverPtr,std::shared_ptr<ThreadSafeQueue<MatF>> sendQueue,QObject *parent = nullptr);

    bool getPause() const;
    void setPause(bool value);

    bool getStarted() const;
    void setStarted(bool value);
    enum SendMode{BFM,G8M};
    SendMode getSendMode() const;
    void setSendMode(const SendMode &value);

    double getLambda() const;
    bool getCenter() const;
    void setCenter(bool value);

private  slots:
    void setLambda(int value);

private:
    std::shared_ptr<ThreadSafeQueue<MatF>> sendQueue;
    QUdpSocket mUdpSock;
    bool started;
    bool pause;
    int interval;
    bool first;
    bool hasShape;
    bool center;
    std::shared_ptr<MMSolver> solverPtr;
    std::shared_ptr<MMSolver> g8mSolverPtr;
    SendMode sendMode;
    MatF G;
    MatF B;
    MatF X;
    MatF A;
    double lambda;
    void sendBroadcast();
    QVector<QHostAddress> getBroadcastAddressFromInterfaces();

    // QThread interface
protected:
    void run();
};

#endif // UDPWORKTHREAD_H
