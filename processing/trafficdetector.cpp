#include "trafficdetector.h"
#include "BackgroundDetector.h"
#include "qtipl.h"

#include <QDebug>

TrafficDetector::TrafficDetector(QObject *parent) : QObject(parent)
{

}

void TrafficDetector::receiveFrameToProcess(QImage* frame){
//    IplImage* processedFrame = QImageToIplImage(frame);

//    CBackgroundDetector detector;
//    detector.newImage(processedFrame);

//    uchar *data;
//    QImage *finalFrame = IplImageToQImage(processedFrame, &data);

    emit sendProcessedFrame(frame);
}
