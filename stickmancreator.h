#ifndef STICKMANCREATOR_H
#define STICKMANCREATOR_H

#include "mariostickman.h"

#include <QJsonObject>

enum StickmanType
{
    MARIO
};

class StickmanCreator
{
public:
    StickmanCreator(const QJsonObject& m_parser);
    virtual ~StickmanCreator();

    virtual Stickman* newStickman(enum StickmanType type);

private:
    QJsonObject m_parser;
};

#endif // STICKMANCREATOR_H
