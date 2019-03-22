#include "mario.h"

Mario::Mario(const QJsonObject& parser)
    : m_parser(parser)
{}

void Mario::buildStickman()
{
    SizeType size;
    std::string sizeString = m_parser["size"].toString().toStdString();
    if(sizeString == "tiny") size = SizeType::TINY;
    if(sizeString == "nrormal") size = SizeType::NORMAL;
    if(sizeString == "large") size = SizeType::LARGE;
    if(sizeString == "giant") size = SizeType::GIANT;
    m_mario = new Stickman(size, m_parser["initialX"].toString().toInt());
}

void Mario::buildLevel()
{
    m_level = new Level(m_mario,
                        m_parser["background"].toString(),
                        m_parser["initialVelocity"].toString().toInt(),
                        m_parser["music"].toString());
}

Level* Mario::getLevel()
{
    return m_level;
}

Mario::~Mario()
{
    delete m_level;
    delete m_mario;
}
