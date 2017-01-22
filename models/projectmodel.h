#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QString>

#include "processing/trafficdetector.h"

class ProjectModel
{
private:
    QString m_configFileLocation;
    QString m_videoFileLocation;
    QString m_name;
    TrafficDetector* m_trafficDetector;

public:
    ProjectModel();
    ProjectModel(QString configFileLocation);

    bool loadConfig();
    bool saveConfig();

};

#endif // PROJECTMODEL_H
