#ifndef LEVEL_H
#define LEVEL_H

#include "stickman.h"

#include <QImage>
#include <string>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class Level
{
public:
    Level();
    Level(const std::string& backgroundLocation, SizeType size, const std::string& musicLocation);
    ~Level();

    const QImage& getBackground() const;
    unsigned int getFrameWidth() const;
    unsigned int getFrameHeight() const;
    unsigned int getFloorBase() const;
    Stickman& getStickman() const;
    void playMusic();

private:
    QImage m_background;
    Stickman* m_stickman;
    QMediaPlaylist* m_playlist;
    QMediaPlayer* m_music;
    const unsigned int m_frameHeight = 572;
    const unsigned int m_frameWidth = 1487 - 300;
    const unsigned int m_floorBase = 40;
};

#endif // LEVEL_H
