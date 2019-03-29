#include "MarioLevel.h"

//MarioLevel::MarioLevel()
//    : m_offset(0),
//      m_stickman(new Stickman()),
//      m_playlist(new QMediaPlaylist()),
//      m_music(new QMediaPlayer())
//{
//    this->m_playlist->addMedia(QUrl("qrc:/music/part1.mp3"));
//    this->m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
//    m_stickman->setYPosition(this->m_frameHeight - this->m_floorBase - m_stickman->getImageHeight());
//}

//MarioLevel::MarioLevel(const QString& backgroundLocation, SizeType size, int initialX, int screenVelocity, const QString& musicLocation)
//    : m_offset(0),
//      m_background(),
//      m_screenVelocity(screenVelocity),
//      m_stickman(new Stickman(size, initialX, 0)),
//      m_playlist(new QMediaPlaylist()),
//      m_music(new QMediaPlayer())
//{

//    QDir musicPath = QDir::currentPath();
//    QDir imagePath = QDir::currentPath();

//    musicPath.cd("../../../../LonelyStickman/music");
//    imagePath.cd("../../../../LonelyStickman/img");

//    m_background = new QImage(imagePath.path().append("/" + backgroundLocation));
//    m_playlist->addMedia(QUrl::fromLocalFile(musicPath.path().append("/" + musicLocation)));
//    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
//    m_music->setPlaylist(m_playlist);
//    m_stickman->setYPosition(m_frameHeight - m_floorBase - m_stickman->getImageHeight());
//}

MarioLevel::MarioLevel(Stickman* stickman, const QString& backgroundLocation, int screenVelcoity, const QString& musicLocation)
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

MarioLevel::MarioLevel(MarioLevel&& other)
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

MarioLevel& MarioLevel::operator =(MarioLevel&& other)
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

MarioLevel::~MarioLevel()
{
    delete m_background;
    delete m_stickman;
    delete m_playlist;
    delete m_music;
}

unsigned int MarioLevel::getFrameWidth() const
{
    return this->m_frameWidth;
}

unsigned int MarioLevel::getFrameHeight() const
{
    return this->m_frameHeight;
}

const QImage& MarioLevel::getBackground() const
{
    return *m_background;
}

void MarioLevel::moveBackground(QPainter& painter, bool isPaused)
{
    painter.drawImage(m_offset, 0, *m_background, 0, 0, m_frameWidth, m_frameHeight);
    painter.drawImage(m_frameWidth + m_offset, 0, *m_background, 0, 0, m_frameWidth, m_frameHeight);

    if(m_offset <= -m_frameWidth)
        m_offset = 0;

    if(!isPaused) m_offset -= m_screenVelocity;
}

void MarioLevel::placeStickman(QPainter &painter)
{
    painter.drawImage(m_stickman->getXPosition(), m_stickman->getYPosition(), m_stickman->getImage());
}

void MarioLevel::playMusic()
{
    this->m_music->play();
}

void MarioLevel::pauseMusic()
{
    this->m_music->pause();
}

int MarioLevel::getOffset() const
{
    return m_offset;
}
