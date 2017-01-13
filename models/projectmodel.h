#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QString>

class ProjectModel
{
private:
    QString m_configFileLocation;
    QString m_videoFileLocation;
    QString m_name;

public:
    ProjectModel(QString name, QString videoFileLocation);
    ProjectModel(QString configFileLocation);

    bool loadConfig();
    bool saveConfig();

};

#endif // PROJECTMODEL_H
