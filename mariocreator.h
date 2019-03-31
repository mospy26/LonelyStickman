#ifndef MARIOCREATOR_H
#define MARIOCREATOR_H

#include "mario.h"

/**
 * @brief The MarioCreator class
 * The director class for Mario
 */
class MarioCreator
{
public:
    /**
     * @brief MarioCreator
     * @param builder
     * Constructor for the mario director
     */
    MarioCreator(Mario* builder);

    /**
     * @brief create
     * @return generated level
     * Creates level and returns it
     */
    Level* create();

private:
    Mario* m_builder; //The abstract builder for building the level
};

#endif // MARIOCREATOR_H
