#include "stickmancreator.h"

StickmanCreator::StickmanCreator(const QJsonObject& parser)
    : m_parser(parser) {}

Stickman* StickmanCreator::newStickman(enum StickmanType type)
{
    SizeType size;
    QString sizeString = m_parser["size"].toString();
    if(sizeString == "tiny") size = SizeType::TINY;
    if(sizeString == "nrormal") size = SizeType::NORMAL;
    if(sizeString == "large") size = SizeType::LARGE;
    if(sizeString == "giant") size = SizeType::GIANT;
    switch (type) {
        case StickmanType::MARIO:
            return new MarioStickman(size, m_parser["initialX"].toString().toInt());
        default:
            return nullptr;
    }
}
