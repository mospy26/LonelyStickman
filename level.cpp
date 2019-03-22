#include "level.h"
#include <iostream>

int offset = 0;

Level::Level()
    : m_background(":/img/back.png"),
      m_stickman(new Stickman()),
      m_playlist(new QMediaPlaylist()),
      m_music(new QMediaPlayer())
{
    this->m_playlist->addMedia(QUrl("qrc:/music/part1.mp3"));
    this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(const QString& backgroundLocation, SizeType size, int initialX, int screenVelocity, const QString& musicLocation)
    : m_screenVelocity(screenVelocity),
      m_stickman(new Stickman(size, initialX, 0)),
      m_playlist(new QMediaPlaylist()),
      m_music(new QMediaPlayer())
{

    QDir musicPath = QDir::currentPath();
    QDir imagePath = QDir::currentPath();

    musicPath.cd("../../../../LonelyStickman/music");
    imagePath.cd("../../../../LonelyStickman/img");

    m_background = QImage(imagePath.path().append("/" + backgroundLocation));
    this->m_playlist->addMedia(QUrl::fromLocalFile(musicPath.path().append("/" + musicLocation)));
    this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(Stickman* stickman, const QString& backgroundLocation, int screenVelcoity, const QString& musicLocation)
    : m_screenVelocity(screenVelcoity),
      m_stickman(new Stickman()),
      m_playlist(new QMediaPlaylist()),
      m_music(new QMediaPlayer())
{
  *m_stickman = std::move(*stickman);
  QDir musicPath = QDir::currentPath();
  QDir imagePath = QDir::currentPath();

  musicPath.cd("../../../../LonelyStickman/music");
  imagePath.cd("../../../../LonelyStickman/img");

  m_background = QImage(imagePath.path().append("/" + backgroundLocation));
  this->m_playlist->addMedia(QUrl::fromLocalFile(musicPath.path().append("/" + musicLocation)));
  this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
  m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(Level&& other)
    : m_background(other.m_background.copy()),
      m_screenVelocity(other.m_screenVelocity),
      m_stickman(std::move(other.m_stickman)),
      m_playlist(other.m_playlist),
      m_music(other.m_music)
{
    other.m_stickman = nullptr;
    other.m_music = nullptr;
    other.m_playlist = nullptr;
}

Level& Level::operator =(Level&& other)
{
    this->m_background = other.m_background.copy();
    this->m_screenVelocity = other.m_screenVelocity;
    this->m_stickman = std::move(other.m_stickman);
    this->m_playlist = other.m_playlist;
    this->m_music = other.m_music;
    other.m_stickman = nullptr;
    other.m_music = nullptr;
    other.m_playlist = nullptr;
    return *this;
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
    m_stickman->movePlayer(moveUp, moveRight, moveLeft, m_frameHeight - m_floorBase- m_stickman->getImageHeight());
    painter.drawImage(m_stickman->getXPosition(), m_stickman->getYPosition(), m_stickman->getImage());
}

void Level::playMusic()
{
    this->m_music->setPlaylist(this->m_playlist);
    this->m_music->play();
}
