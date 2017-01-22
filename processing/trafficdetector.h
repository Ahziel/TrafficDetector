#ifndef TRAFFICDETECTOR_H
#define TRAFFICDETECTOR_H

#include <QObject>
#include <QImage>
#include <opencv/cv.h>

#include <processing/MotionDetector.h>
#include <processing/BackgroundDetector.h>

class TrafficDetector : public QObject
{
    Q_OBJECT

private:
    IplImage* m_iplFrame;
    IplImage* m_iplFrameGray;
    CMotionDetector* m_motionDetector;
    CBackgroundDetector* m_backgroundDetector;
    double m_threshold;

    void createConnections();

    IplImage* qImage2IplImage(const QImage& qImage);
    QImage iplImage2QImage(const IplImage *iplImage);

public:
    explicit TrafficDetector(QObject *parent = 0);
    ~TrafficDetector();

    void setThreshold(double threshold);

signals:
    void sendMotionFrame(QImage* backgroundFrame);
    void sendProcessedFrame(QImage* processedFrame);
    void sendSetBackgroundDetectorGamma(float gamma);

public slots:
    void receiveFrameToProcess(QImage frame);
    void receiveMotionFrame(IplImage* motion);
    void receiveSetBackgroundDetectorGamma(double gamma);

};

#endif // TRAFFICDETECTOR_H
