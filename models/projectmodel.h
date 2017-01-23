#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QString>

#include "processing/trafficdetector.h"

class ProjectModel
{
private:
    QString m_configFileLocation;
    QString m_videoFileLocation;
    TrafficDetector* m_trafficDetector;

public:
    ProjectModel(TrafficDetector* trafficDetector);
    ProjectModel(QString configFileLocation);

    bool loadConfig();
    bool saveConfig();

    void setConfigFileLocation(const QString &configFileLocation);
    QString getVideoFileLocation() const;
    void setVideoFileLocation(const QString &videoFileLocation);
};

#endif // PROJECTMODEL_H
