#include "level.h"
#include <iostream>

int offset = 0;

Level::Level()
    : m_background(":/img/back.png"), m_stickman(new Stickman()), m_playlist(new QMediaPlaylist()), m_music(new QMediaPlayer())
{
    this->m_playlist->addMedia(QUrl("qrc:/music/part1.mp3"));
    this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(const std::string& backgroundLocation, SizeType size, int initialX, int screenVelocity, const std::string& musicLocation)
    : m_background(QImage(backgroundLocation.c_str())), m_screenVelocity(screenVelocity), m_stickman(new Stickman(size, initialX, 0)), m_playlist(new QMediaPlaylist()), m_music(new QMediaPlayer())
{
    this->m_playlist->addMedia(QUrl(musicLocation.c_str()));
    this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::~Level()
{
    delete m_stickman;
    delete m_playlist;
    delete m_music;
}

unsigned int Level::getFrameWidth() const
{
    return this->m_frameWidth;
}

unsigned int Level::getFrameHeight() const
{
    return this->m_frameHeight;
}

const QImage& Level::getBackground() const
{
    return this->m_background;
}

void Level::moveBackground(QPainter& painter)
{
    painter.drawImage(offset, 0, m_background, 0, 0, m_frameWidth, m_frameHeight);
    painter.drawImage(m_frameWidth + offset, 0, m_background, 0, 0, m_frameWidth, m_frameHeight);

    if(offset <= -m_frameWidth)
        offset = 0;

    offset -= m_screenVelocity;

}

void Level::placeStickman(QPainter &painter, bool moveUp, bool moveRight, bool moveLeft)
{
    painter.drawImage(m_stickman->getXPosition(), m_stickman->getYPosition(), m_stickman->getImage());
}

void Level::playMusic()
{
    this->m_music->setPlaylist(this->m_playlist);
    this->m_music->play();
}
