#include "cameraworkthread.h"
#include "threadsynglobalobj.h"
void CameraWorkThread::readCamera()
{
    std::lock_guard<std::mutex> lock(sets.obj.cameraTheadMutex);//lock
    if(!stopSignal){
        (*camera)>>image;       
        //std::cout<<image.size()<<std::endl<<std::flush;
        cv::Mat left=image(leftRect).clone();
        if(dataQueue->TryPush(left)){//after get the lock,must not to wait
            emit returnData();
        }
    }
}

bool CameraWorkThread::getStopSignal() const
{
    return stopSignal;
}

void CameraWorkThread::setStopSignal(bool value)
{
    stopSignal = value;
}

bool CameraWorkThread::getPause() const
{
    return pause;
}

void CameraWorkThread::setPause(bool value)
{
    pause = value;
}

void CameraWorkThread::run()
{
    state=RUNNING;
    while (!stopSignal) {
        if (isInterruptionRequested())
            return;
        if(pause){
            msleep(interval*2);
        }else{
            readCamera();
            msleep(interval);
        }
//        readCamera();
//        msleep(interval);
    }
    state=STOPED;
}
