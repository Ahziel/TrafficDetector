#include "models/projectmodel.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

ProjectModel::ProjectModel(TrafficDetector* trafficDetector)
{
    m_trafficDetector = trafficDetector;
    m_name = "New_Project";
    m_configFileLocation = m_name.append(".xml");
    // remmplacer par un setter qui rajoute tjr le .xml
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
    xmlWriter.writeTextElement("ProjectName", m_name);
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
               // qDebug() << "[DEBUG]ProjectModel::loadConfig(): Read element "<< xmlReader.name() << " containing " << xmlReader.readElementText();
            }

            //#TODO Add the rest of the elements (consider using a hashmap ?)
        }
    }

    if(xmlReader.hasError()){
        qDebug() << "[ERROR]ProjectModel::loadConfig(): Could not parse config file, check for syntax error";
    }

    file.close();
    return true;
}
