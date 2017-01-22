#ifndef TRAFFICDETECTOR_H
#define TRAFFICDETECTOR_H

#include <QObject>
#include <QImage>
#include <QVector>
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
    int m_output;
    int m_dilation;
    int m_erosion;
    QVector<int> m_counter;

    void createConnections();

    IplImage* qImage2IplImage(const QImage& qImage);
    QImage iplImage2QImage(const IplImage *iplImage);

public:
    explicit TrafficDetector(QObject *parent = 0);
    ~TrafficDetector();

signals:
    void sendMotionFrame(QImage* motionFrame);
    void sendBackgroundFrame(QImage* backgroundFrame);
    void sendProcessedFrame(QImage* processedFrame);
    void sendSetBackgroundDetectorGamma(float gamma);
    void countedVehicules(int vehicules);

public slots:
    void receiveFrameToProcess(QImage frame);
    void receiveMotionFrame(IplImage* motion);
    void receiveSetBackgroundDetectorGamma(double gamma);
    void receiveSetThreshold(int threshold);
    void receiveSetDilation(int dilation);
    void receiveSetErosion(int erosion);
    void receiveOutputChange(int index);

};

#endif // TRAFFICDETECTOR_H
