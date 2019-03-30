#ifndef MARIO_H
#define MARIO_H

#include "gamebuilder.h"

/**
 * @brief The Mario class
 * Concrete Builder
 */
class Mario : public GameBuilder
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
    void buildStickman() override;

    /**
     * @brief buildLevel
     * Overrides from base class
     */
    void buildLevel() override;

    /**
     * @brief getLevel
     * @return created level
     * Overrides base class
     */
    Level* getLevel() override;

private:
    Stickman* m_mario;
    Level* m_level;
    QJsonObject m_parser;
};

#endif // MARIO_H
