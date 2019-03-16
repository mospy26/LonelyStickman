#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <istream>
#include <QFile>
#include <QTextStream>

enum Configuration
{
    SIZE,
    INITIAL_X,
    INITIAL_VELOCITY,
    BACKGROUND,
    MUSIC,
    ERROR
};

class ConfigParser
{
public:
    ConfigParser(const QString& filePath);

    const std::string& operator[](const Configuration& key);

    Configuration hash(std::string key);

private:
    std::map<int, std::string> m_dictionary;
};

#endif // CONFIGPARSER_H
