#include "level.h"

Level::Level()
    : m_background(":/img/back.png"), m_stickman(new Stickman())
{
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(const std::string& backgroundLocation, SizeType size)
    : m_background(QImage(backgroundLocation.c_str())), m_stickman(new Stickman(size))
{
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(const QImage& background, SizeType size)
    : m_background(background), m_stickman(new Stickman(size))
{
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(const QImage& background, Stickman* stickman)
    : m_background(background), m_stickman(stickman)
{
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::~Level()
{
    delete m_stickman;
}

unsigned int Level::getFrameWidth() const
{
    return this->m_frameWidth;
}

unsigned int Level::getFrameHeight() const
{
    return this->m_frameHeight;
}

unsigned int Level::getFloorBase() const
{
    return this->m_floorBase;
}

Stickman& Level::getStickman() const
{
    return *this->m_stickman;
}

const QImage& Level::getBackground() const
{
    return this->m_background;
}
