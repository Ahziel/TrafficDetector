#include "trafficdetector.h"
#include "BackgroundDetector.h"
#include "qtipl.h"

#include <QDebug>

TrafficDetector::TrafficDetector(QObject *parent) : QObject(parent)
{
    m_motionDetector = new CMotionDetector();
    m_backgroundDetector = new CBackgroundDetector();
    m_threshold = 50;
    m_output = 0;
    m_dilation = 2;
    m_erosion = 2;

    createConnections();
}


float TrafficDetector::getGamma() const
{
    return m_backgroundDetector->getGamma();
}

double TrafficDetector::getThreshold() const
{
    return m_threshold;
}

int TrafficDetector::getDilation() const
{
    return m_dilation;
}

int TrafficDetector::getErosion() const
{
    return m_erosion;
}

void TrafficDetector::setGamma(double gamma)
{
    emit sendSetBackgroundDetectorGamma((float) gamma);
    emit sendChangedGamma(gamma);
}

void TrafficDetector::setThreshold(double threshold)
{
    m_threshold = threshold;
    emit sendChangedThreshold(threshold);
}

void TrafficDetector::setOutput(int output)
{
    m_output = output;
}

void TrafficDetector::setDilation(int dilation)
{
    m_dilation = dilation;
    emit sendChangedDilation(dilation);
}

void TrafficDetector::setErosion(int erosion)
{
    m_erosion = erosion;
    emit sendChangedErosion(erosion);
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

}

void TrafficDetector::receiveMotionFrame(IplImage* motion)
{
    // Motion ouput
    QImage motionFrame = iplImage2QImage(motion);
    //-----

    // Background output
    IplImage* iplFrameBackground = m_backgroundDetector->calculus(m_iplFrame, motion);
    QImage backgroundFrame = iplImage2QImage(iplFrameBackground);
    // ------

    // Processing
    // ======
    cv::Mat matFrameBackground(iplFrameBackground);
    cv::Mat matFrameGray(m_iplFrameGray);
    cv::Mat matProcessedFrame;

    // Thresholding
    cv::absdiff(matFrameGray, matFrameBackground, matProcessedFrame);
    cv::threshold(matProcessedFrame, matProcessedFrame, m_threshold, 255, CV_THRESH_BINARY);

    // Morphological operations
    cv::Mat dilationElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(m_dilation, m_dilation));
    cv::Mat erossionElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(m_erosion, m_erosion));

    cv::dilate(matProcessedFrame, matProcessedFrame, dilationElement);
    cv::dilate(matProcessedFrame, matProcessedFrame, dilationElement);
    cv::erode(matProcessedFrame, matProcessedFrame, erossionElement);
    cv::erode(matProcessedFrame, matProcessedFrame, erossionElement);

    cv::dilate(matProcessedFrame, matProcessedFrame, dilationElement);
    cv::dilate(matProcessedFrame, matProcessedFrame, dilationElement);
    cv::erode(matProcessedFrame, matProcessedFrame, erossionElement);

    // Outline research
    std::vector<std::vector<cv::Point>> outlines;
    cv::Mat matOutlineFrame = matProcessedFrame.clone();

    cv::findContours(matOutlineFrame, outlines, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Outline output
    IplImage iplOutlineFrame = matOutlineFrame;
    QImage outlineFrame = iplImage2QImage(&iplOutlineFrame);
    // -----

    // Counting vehicules
    int count = 0;
    for(auto outline : outlines)
    {
        if(outline.size() > 40)
        {
            count++;
        }
    }

    if(m_counter.size() == 29)
    {
        m_counter.pop_back();
    }

    m_counter.push_front(count);

    int sum = 0;
    for(int c : m_counter)
    {
        sum += c;
    }

    emit countedVehicules(sum / m_counter.size());
    // -----

    switch (m_output) {
    case 0: //background
        emit sendProcessedFrame(&backgroundFrame);
        break;
    case 1: //outline
        emit sendProcessedFrame(&outlineFrame);
        break;
    case 2: //shape
        emit sendProcessedFrame(&motionFrame);
        break;
    default:
        break;
    }
}

void TrafficDetector::receiveSetBackgroundDetectorGamma(double gamma)
{
    emit sendSetBackgroundDetectorGamma((float) gamma);
}

void TrafficDetector::receiveSetThreshold(int threshold)
{
    if(m_threshold != threshold)
    {
        m_threshold = threshold;
    }
}

void TrafficDetector::receiveSetDilation(int dilation)
{
    if(m_dilation != dilation)
    {
        m_dilation = dilation;
    }
}

void TrafficDetector::receiveSetErosion(int erosion)
{
    if(m_erosion != erosion)
    {
        m_erosion = erosion;
    }
}

void TrafficDetector::receiveOutputChange(int index)
{
    if(m_output != index)
    {
        m_output = index;
    }
}
