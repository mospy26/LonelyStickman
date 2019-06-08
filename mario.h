#ifndef MARIO_H
#define MARIO_H

#include "level.h"
#include "stickman.h"
#include <QJsonObject>

/**
 * @brief The Mario class
 * Concrete Builder
 */
class Mario
{
public:
    /**
     * @brief Mario
     * @param parser
     * Constructor for mario builder
     */
    explicit Mario(const QJsonObject& parser);

    ~Mario();

    /**
     * @brief buildStickman
     * Overrides from base class
     */
    void buildStickman();

    /**
     * @brief buildLevel
     * Overrides from base class
     */
    void buildLevel();

    /**
     * @brief getLevel
     * @return created level
     */
    Level* getLevel();

private:
    Stickman* m_mario;
    Level* m_level;
    QJsonObject m_parser;
};

#endif // MARIO_H
