#include "levelcreator.h"

LevelCreator::LevelCreator(const QJsonObject& parser)
    : m_parser(parser) {}

Level* LevelCreator::newLevel(Stickman* stickman)
{
//    return new Level(stickman,
//                        m_parser["background"].toString(),
//                        m_parser["initialVelocity"].toString().toInt(),
//                        m_parser["music"].toString());
    return nullptr;
}
