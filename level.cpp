#include "level.h"
#include <iostream>

Level::Level()
    : m_background(":/img/back.png"), m_stickman(new Stickman()), m_playlist(new QMediaPlaylist()), m_music(new QMediaPlayer())
{
    this->m_playlist->addMedia(QUrl("qrc:/music/part1.mp3"));
    this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(const std::string& backgroundLocation, SizeType size, const std::string& musicLocation)
    : m_background(QImage(backgroundLocation.c_str())), m_stickman(new Stickman(size)), m_playlist(new QMediaPlaylist()), m_music(new QMediaPlayer())
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

void Level::playMusic()
{
    this->m_music->setPlaylist(this->m_playlist);
    this->m_music->play();
}
