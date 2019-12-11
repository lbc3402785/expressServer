#ifndef CAMERAWORKTHREAD_H
#define CAMERAWORKTHREAD_H
#include <opencv2/opencv.hpp>
#include <QThread>
#include <mutex>
#include "settings.h"
#include "thread/threadsafequeue.h"
#include "workingthread.h"
class CameraWorkThread : public WorkingThread{
    Q_OBJECT
public:
    CameraWorkThread(std::shared_ptr<ThreadSafeQueue<cv::Mat>> dataQueue,std::shared_ptr<cv::VideoCapture> camera,QObject *parent = nullptr)
        :dataQueue(dataQueue),camera(camera),WorkingThread(parent)
    {
        stopSignal=false;
        pause=false;
        leftRect=cv::Rect(0,0,sets.getWidth(),sets.getHeight());
        interval=sets.getInterval();
    }

    void readCamera();
    bool getStopSignal() const;
    void setStopSignal(bool value);

    bool getPause() const;
    void setPause(bool value);

private:
    int id;
    int interval;
    bool pause;
    cv::Mat image;
    std::shared_ptr<ThreadSafeQueue<std::vector<cv::Point>>> landMarksQueue;
    std::shared_ptr<ThreadSafeQueue<cv::Mat>> dataQueue;
    std::shared_ptr<cv::VideoCapture> camera;
    cv::Rect leftRect;
signals:
    void returnData();
    void capturedSuccessful();

    // QThread interface
protected:
    void run();
};

#endif // CAMERAWORKTHREAD_H

