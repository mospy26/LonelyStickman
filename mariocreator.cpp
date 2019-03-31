#include "mariocreator.h"

MarioCreator::MarioCreator(Mario* builder)
    : m_builder(builder) {}

Level* MarioCreator::create()
{
    m_builder->buildStickman();
    m_builder->buildLevel();
    return m_builder->getLevel();
}
