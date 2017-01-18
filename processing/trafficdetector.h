#ifndef TRAFFICDETECTOR_H
#define TRAFFICDETECTOR_H

#include <QObject>
#include <QImage>

class TrafficDetector : public QObject
{
    Q_OBJECT
public:
    explicit TrafficDetector(QObject *parent = 0);

signals:
    void sendProcessedFrame(QImage* processedFrame);

public slots:
    void receiveFrameToProcess(QImage* frame);

};

#endif // TRAFFICDETECTOR_H
