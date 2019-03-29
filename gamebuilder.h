#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "dialog.h"

class GameBuilder
{
public:
    GameBuilder() {}
    virtual void buildStickman() = 0;
    virtual void buildLevel() = 0;
    virtual Level* getLevel() = 0;
    virtual ~GameBuilder() {}
};

#endif // GAMEBUILDER_H
