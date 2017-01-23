#include "models/projectmodel.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

ProjectModel::ProjectModel(TrafficDetector* trafficDetector)
{
    m_trafficDetector = trafficDetector;
    m_configFileLocation = "";
    m_videoFileLocation = "";

}

ProjectModel::ProjectModel(QString configFileLocation)
{
    m_configFileLocation = configFileLocation;
    loadConfig();
}

void ProjectModel::setConfigFileLocation(const QString &configFileLocation)
{
    m_configFileLocation = configFileLocation;
}

QString ProjectModel::getVideoFileLocation() const
{
    return m_videoFileLocation;
}

void ProjectModel::setVideoFileLocation(const QString &videoFileLocation)
{
    m_videoFileLocation = videoFileLocation;
}

bool ProjectModel::saveConfig()
{
    QFile file(m_configFileLocation);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "[ERROR]ProjectModel::saveConfig(): Unable to open file";
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("TrafficDetectorProjectConfig");
    xmlWriter.writeTextElement("VideoFileLocation", m_videoFileLocation);
    xmlWriter.writeTextElement("TrafficDetectorGamma", QString::number(m_trafficDetector->getGamma()));
    xmlWriter.writeTextElement("TrafficDetectorThreshold", QString::number(m_trafficDetector->getThreshold()));
    xmlWriter.writeTextElement("TrafficDetectorDilation", QString::number(m_trafficDetector->getDilation()));
    xmlWriter.writeTextElement("TrafficDetectorErosion", QString::number(m_trafficDetector->getErosion()));
    xmlWriter.writeEndDocument();
    file.close();

    return true;
}

bool ProjectModel::loadConfig()
{
    QFile file(m_configFileLocation);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "[ERROR]ProjectModel::loadConfig(): Unable to open file";
        return false;
    }

    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if(token == QXmlStreamReader::StartDocument){
            continue;
        }

        if(token == QXmlStreamReader::StartElement){
            if(xmlReader.name() == "VideoFileLocation"){
               m_videoFileLocation = xmlReader.readElementText();
            }


            if(xmlReader.name() == "TrafficDetectorGamma"){
               double gamma = xmlReader.readElementText().toDouble();
               m_trafficDetector->setGamma(gamma);
            }


            if(xmlReader.name() == "TrafficDetectorThreshold"){
               double threshold = xmlReader.readElementText().toDouble();
               m_trafficDetector->setThreshold(threshold);
            }


            if(xmlReader.name() == "TrafficDetectorDilation"){
               int dilation = xmlReader.readElementText().toInt();
               m_trafficDetector->setDilation(dilation);
            }


            if(xmlReader.name() == "TrafficDetectorErosion"){
               int erosion = xmlReader.readElementText().toInt();
               m_trafficDetector->setErosion(erosion);
            }


        }
    }

    if(xmlReader.hasError()){
        qDebug() << "[ERROR]ProjectModel::loadConfig(): Could not parse config file, check for syntax error";
    }

    file.close();
    return true;
}
