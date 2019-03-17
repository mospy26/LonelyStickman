#include "configparser.h"
#include "stickman.h"

ConfigParser::ConfigParser(const QString& filePath)
{
    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly)) {
       QTextStream in(&inputFile);
       std::string key;
       std::string value;
       while (!in.atEnd())
       {
          QString qLine = in.readLine();
          std::string line = qLine.toStdString();
          std::stringstream input(line);
          std::getline(input, key, '=');
          std::getline(input, value, '\n');
          switch(hash(key)) {
              case Configuration::SIZE:
                  m_dictionary[Configuration::SIZE] = value;
                  break;
              case Configuration::INITIAL_X:
                  m_dictionary[Configuration::INITIAL_X] = value;
                  break;
              case Configuration::INITIAL_VELOCITY:
                  m_dictionary[INITIAL_VELOCITY] = value;
                  break;
              case Configuration::BACKGROUND:
                  m_dictionary[Configuration::BACKGROUND] = value;
                  break;
              case Configuration::MUSIC:
                  m_dictionary[Configuration::MUSIC] = value;
                  break;
              default:
                 break;
          }
       }
    }
    inputFile.close();
}

const std::string& ConfigParser::operator[](const Configuration& key)
{
    return this->m_dictionary[key];
}

Configuration ConfigParser::hash(std::string key)
{
    if(key == "size") return Configuration::SIZE;
    if(key == "initialX") return Configuration::INITIAL_X;
    if(key == "initialVelocity") return Configuration::INITIAL_VELOCITY;
    if(key == "background") return Configuration::BACKGROUND;
    if(key == "music") return Configuration::MUSIC;
    return Configuration::ERROR;
}
