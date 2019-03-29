#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "level.h"

#include <QJsonObject>

class LevelCreator
{
public:
    LevelCreator(const QJsonObject& parser);
    virtual ~LevelCreator();

    virtual Level* newLevel(Stickman* stickman);

private:
    QJsonObject m_parser;
};

#endif // LEVELCREATOR_H
