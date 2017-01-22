#include "trafficdetector.h"
#include "BackgroundDetector.h"
#include "qtipl.h"

#include <QDebug>

TrafficDetector::TrafficDetector(QObject *parent) : QObject(parent)
{
    m_motionDetector = new CMotionDetector();
    m_backgroundDetector = new CBackgroundDetector();

    createConnections();
}

void TrafficDetector::createConnections()
{
    connect(m_motionDetector, SIGNAL(calculusNewImage(IplImage*)), this, SLOT(receiveMotionFrame(IplImage*)));
    connect(this, SIGNAL(sendSetBackgroundDetectorGamma(float)), m_backgroundDetector, SLOT(setGamma(float)));
}


TrafficDetector::~TrafficDetector()
{
    delete m_motionDetector;
    delete m_backgroundDetector;
    cvReleaseImage(&m_iplFrame);
    cvReleaseImage(&m_iplFrameGray);
}

IplImage* TrafficDetector::qImage2IplImage(const QImage& qImage)
{
    int width = qImage.width();
    int height = qImage.height();

    // Creates a iplImage with 3 channels
    IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
    char * imgBuffer = img->imageData;

    //Remove alpha channel
    int jump = (qImage.hasAlphaChannel()) ? 4 : 3;

    for (int y=0;y<img->height;y++){
        QByteArray a((const char*)qImage.scanLine(y), qImage.bytesPerLine());
        for (int i=0; i<a.size(); i+=jump){
            //Swap from RGB to BGR
            imgBuffer[2] = a[i];
            imgBuffer[1] = a[i+1];
            imgBuffer[0] = a[i+2];
            imgBuffer+=3;
        }
    }

    return img;
}

QImage TrafficDetector::iplImage2QImage(const IplImage *iplImage) {

    int height = iplImage->height;
    int width = iplImage->width;

    if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
        const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
        QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
        return img.rgbSwapped();
    } else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){

        const uchar *qImageBuffer = (const uchar*)iplImage->imageData; QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);

        QVector<QRgb> colorTable; for (int i = 0; i < 256; i++){ colorTable.push_back(qRgb(i, i, i)); } img.setColorTable(colorTable); return img;

    }else{
        qWarning() << "Image cannot be converted.";
        return QImage();
    }

}

void TrafficDetector::receiveFrameToProcess(QImage frame)
{
//    if(m_iplFrame == nullptr && m_iplFrameGray == nullptr){
//        cvReleaseImage(&m_iplFrame);
//        cvReleaseImage(&m_iplFrameGray);
//    }

    m_iplFrame = qImage2IplImage(frame);
    m_iplFrameGray = cvCreateImage(cvSize(m_iplFrame->width, m_iplFrame->height), IPL_DEPTH_8U, 1);
    cvCvtColor(m_iplFrame, m_iplFrameGray, CV_BGR2GRAY);
    m_motionDetector->newImage(m_iplFrame);

//    emit sendProcessedFrame(&frame);

}

void TrafficDetector::receiveMotionFrame(IplImage* motion)
{
    IplImage* iplFrameBackground = m_backgroundDetector->calculus(m_iplFrame, motion);
    IplImage* iplProcessedFrame = cvCreateImage(cvSize(m_iplFrame->width, m_iplFrame->height), IPL_DEPTH_8U, 1);
    cvAbsDiff(m_iplFrameGray, iplFrameBackground, iplProcessedFrame);

    QImage processedFrame = iplImage2QImage(motion);
    emit sendProcessedFrame(&processedFrame);
}

void TrafficDetector::receiveSetBackgroundDetectorGamma(float gamma)
{
    emit sendSetBackgroundDetectorGamma(gamma);
}

