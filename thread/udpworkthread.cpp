#include "udpworkthread.h"
#include <QDebug>
#include <QJsonObject>
#include "threadsynglobalobj.h"
void printJson(const QJsonObject &result) {
    qDebug() << result;
}
template <typename T>
QJsonArray toJson(const std::vector<T>& myVec) {
    QJsonArray result;
    std::copy (myVec.begin(), myVec.end(), std::back_inserter(result));
    return result;
}
UdpWorkThread::UdpWorkThread(std::shared_ptr<MMSolver> solverPtr,std::shared_ptr<MMSolver> g8mSolverPtr,std::shared_ptr<ThreadSafeQueue<MatF>> landMarksQueue,QObject *parent)
    :solverPtr(solverPtr),g8mSolverPtr(g8mSolverPtr),sendQueue(landMarksQueue), WorkingThread(parent)
{
    first=true;
    stopSignal=false;
    pause=false;
    interval=sets.getInterval();
    mUdpSock.bind(1234, QUdpSocket::ShareAddress);
    sendMode=BFM;
}

bool UdpWorkThread::getPause() const
{
    return pause;
}

void UdpWorkThread::setPause(bool value)
{
    pause = value;
    if(pause){
        state=PAUSED;
    }
    else{
        state=RUNNING;
    }
}

bool UdpWorkThread::getStarted() const
{
    return started;
}

void UdpWorkThread::setStarted(bool value)
{
    started = value;
}

UdpWorkThread::SendMode UdpWorkThread::getSendMode() const
{
    return sendMode;
}

void UdpWorkThread::setSendMode(const SendMode &value)
{
    sendMode = value;
}

double UdpWorkThread::getLambda() const
{
    return lambda;
}

void UdpWorkThread::setLambda(int value)
{
    lambda = value;
}

bool UdpWorkThread::getCenter() const
{
    return center;
}

void UdpWorkThread::setCenter(bool value)
{
    center = value;
}

void UdpWorkThread::sendBroadcast()
{
    std::lock_guard<std::mutex> lock(sets.obj.udpTheadMutex);//lock
    if(!stopSignal){
        std::shared_ptr<MatF> KPPtr=sendQueue->TryPop();
        if(KPPtr){
            QJsonObject obj;
            if(sendMode==BFM){
                if(first){
                    fitting::ModelFitting::fittingShape(*KPPtr,*solverPtr,center);
                    first=false;
                }else{
                    fitting::ModelFitting::fittingExpression(*KPPtr,*solverPtr,center);
                }
                std::vector<float> shapeParams(solverPtr->SX.data(),solverPtr->SX.data()+solverPtr->SX.rows());
                std::vector<float> expressParams(solverPtr->EX.data(),solverPtr->EX.data()+solverPtr->EX.rows());
                obj["shapeX"]=toJson(shapeParams);
                obj["expressX"]=toJson(expressParams);
                std::cout<<"solverPtr->EX:"<<solverPtr->EX<<std::endl<<std::flush;
            }else{
                fitting::ModelFitting::fittingExpression(*KPPtr,*g8mSolverPtr,center);
                std::cout<<"g8mSolverPtr->EX:"<<g8mSolverPtr->EX<<std::endl<<std::flush;
                std::vector<float> g8Params(g8mSolverPtr->EX.data(),g8mSolverPtr->EX.data()+g8mSolverPtr->EX.rows());
                obj["G8M"]=toJson(g8Params);
            }

            //std::cout<<"444"<<std::endl<<std::flush;
            //printJson(obj);
            QVector<QHostAddress> addresses = getBroadcastAddressFromInterfaces();
            QByteArray data(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            foreach (QHostAddress address, addresses) {
                mUdpSock.writeDatagram(data, address, sets.getPort());
            }
            QHostAddress add("10.66.20.114");
            //QHostAddress add("127.0.0.1");
            mUdpSock.writeDatagram(data, add, 10001);
        }

    }
}

QVector<QHostAddress> UdpWorkThread::getBroadcastAddressFromInterfaces()
{
    QVector<QHostAddress> addresses;
    foreach (QNetworkInterface iface, QNetworkInterface::allInterfaces()) {
        if (iface.flags() & QNetworkInterface::CanBroadcast) {
            foreach (QNetworkAddressEntry addressEntry, iface.addressEntries()) {
                if (!addressEntry.broadcast().isNull()) {
                    addresses.push_back(addressEntry.broadcast());
                }
            }
        }
    }
    return addresses;
}


void UdpWorkThread::run()
{
    state=RUNNING;
    while (!stopSignal) {
        if (isInterruptionRequested())
            return;
        if(pause){
            msleep(interval*2);
        }else{
            sendBroadcast();
            msleep(interval);
        }
    }
    state=STOPED;
}
