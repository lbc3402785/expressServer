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
UdpWorkThread::UdpWorkThread(std::shared_ptr<MMSolver> solverPtr,std::shared_ptr<ThreadSafeQueue<MatF>> landMarksQueue,QObject *parent)
    :solverPtr(solverPtr),sendQueue(landMarksQueue), WorkingThread(parent)
{
    first=true;
    stopSignal=false;
    pause=false;
    interval=sets.getInterval();
    mUdpSock.bind(sets.getPort(), QUdpSocket::ShareAddress);
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

void UdpWorkThread::sendBroadcast()
{
    std::lock_guard<std::mutex> lock(sets.obj.udpTheadMutex);//lock
    if(!stopSignal){
        std::shared_ptr<MatF> KPPtr=sendQueue->TryPop();
        if(KPPtr){

            std::cout<<"11111"<<std::endl<<std::flush;
            if(first){
                fitting::ModelFitting::fittingShape(*KPPtr,*solverPtr);
                first=false;
            }
            std::cout<<"2222"<<std::endl<<std::flush;
            fitting::ModelFitting::fittingExpression(*KPPtr,*solverPtr);
            QJsonObject obj;
            std::cout<<"333"<<std::endl<<std::flush;
            std::vector<float> params(solverPtr->EX.data(),solverPtr->EX.data()+solverPtr->EX.rows());
            //        for(int i=0;i<solverPtr->EX.rows();i++){
            //            std::cout<<params[i]-solverPtr->EX(i,0)<<std::endl;
            //        }
            obj["expressX"]=toJson(params);
            std::cout<<"444"<<std::endl<<std::flush;
            //printJson(obj);
            //        QVector<QHostAddress> addresses = getBroadcastAddressFromInterfaces();
            //        QByteArray data(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            //        foreach (QHostAddress address, addresses) {
            //            mUdpSock.writeDatagram(data, address, sets.getPort());
            //        }
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
