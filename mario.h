#ifndef MARIO_H
#define MARIO_H

#include "gamebuilder.h"

class Mario : public GameBuilder
{
public:
    Mario(const QJsonObject& parser);
    ~Mario();

    void buildStickman();
    void buildLevel();
    Level* getLevel();

private:
    Stickman* m_mario;
    Level* m_level;
    QJsonObject m_parser;
};

#endif // MARIO_H
