#ifndef LEVEL_H
#define LEVEL_H

#include <QImage>
#include <string>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "stickman.h"

class Level
{
public:
    Level();
    Level(const std::string& backgroundLocation, SizeType size);
    Level(const QImage& background, SizeType size);
    Level(const QImage& background, Stickman* stickman);
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
    //stickman.positiony = frame width - floor base - m_stickman->current base
};

#endif // LEVEL_H
