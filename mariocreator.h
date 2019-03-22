#ifndef MARIOCREATOR_H
#define MARIOCREATOR_H

#include "mario.h"

class MarioCreator
{
public:
    MarioCreator(GameBuilder* builder);
    Level* create();

private:
    GameBuilder* m_builder;

};

#endif // MARIOCREATOR_H
