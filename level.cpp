#include "level.h"
#include <iostream>

Level::Level(const QString& backgroundLocation, SizeType size, int initialX, int screenVelocity, const QString& musicLocation)
    : m_offset(0),
      m_background(),
      m_screenVelocity(screenVelocity),
      m_stickman(new Stickman(size, initialX, 0)),
      m_playlist(new QMediaPlaylist()),
      m_music(new QMediaPlayer())
{

    QDir musicPath = QDir::currentPath();
    QDir imagePath = QDir::currentPath();

    musicPath.cd("../../../../LonelyStickman/music");
    imagePath.cd("../../../../LonelyStickman/img");

    m_background = new QImage(imagePath.path().append("/" + backgroundLocation));
    m_playlist->addMedia(QUrl::fromLocalFile(musicPath.path().append("/" + musicLocation)));
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_music->setPlaylist(m_playlist);
    m_stickman->setYPosition(m_frameHeight - m_floorBase - m_stickman->getImageHeight());
}

Level::Level(Stickman* stickman, const QString& backgroundLocation, int screenVelcoity, const QString& musicLocation)
    : m_offset(0),
      m_screenVelocity(screenVelcoity),
      m_stickman(new Stickman()),
      m_playlist(new QMediaPlaylist()),
      m_music(new QMediaPlayer())
{
  *m_stickman = std::move(*stickman);
  QDir musicPath = QDir::currentPath();
  QDir imagePath = QDir::currentPath();

  musicPath.cd("../../../../LonelyStickman/music");
  imagePath.cd("../../../../LonelyStickman/img");

  m_background = new QImage(imagePath.path().append("/" + backgroundLocation));
  this->m_playlist->addMedia(QUrl::fromLocalFile(musicPath.path().append("/" + musicLocation)));
  this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
  m_music->setPlaylist(m_playlist);
  m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
}

Level::Level(Level&& other)
    : m_background(other.m_background),
      m_screenVelocity(other.m_screenVelocity),
      m_stickman(std::move(other.m_stickman)),
      m_playlist(other.m_playlist),
      m_music(other.m_music)
{
    other.m_background = nullptr;
    other.m_stickman = nullptr;
    other.m_music = nullptr;
    other.m_playlist = nullptr;
}

Level& Level::operator =(Level&& other)
{
    this->m_background = other.m_background;
    this->m_screenVelocity = other.m_screenVelocity;
    this->m_stickman = std::move(other.m_stickman);
    this->m_playlist = other.m_playlist;
    this->m_music = other.m_music;
    other.m_background = nullptr;
    other.m_stickman = nullptr;
    other.m_music = nullptr;
    other.m_playlist = nullptr;
    return *this;
}

Level::~Level()
{
    delete m_background;
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
    return *m_background;
}

void Level::moveBackground(QPainter& painter, bool isPaused)
{
    painter.drawImage(m_offset, 0, *m_background, 0, 0, m_frameWidth, m_frameHeight);
    painter.drawImage(m_frameWidth + m_offset, 0, *m_background, 0, 0, m_frameWidth, m_frameHeight);

    if(m_offset <= -m_frameWidth)
        m_offset = 0;

    if(!isPaused) m_offset -= m_screenVelocity;
}

void Level::placeStickman(QPainter &painter)
{
    painter.drawImage(m_stickman->getXPosition(), m_stickman->getYPosition(), m_stickman->getImage());
}

void Level::playMusic()
{
    this->m_music->play();
}

void Level::pauseMusic()
{
    this->m_music->pause();
}

int Level::getOffset() const
{
    return m_offset;
}
