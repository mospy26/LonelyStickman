#ifndef LEVEL_H
#define LEVEL_H

#include "stickman.h"

#include <QImage>
#include <QPainter>
#include <string>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>

class Level
{
public:
    Level();
    Level(const QString& backgroundLocation, SizeType size, int initialX, int screenVelocity, const QString& musicLocation);
    Level(Stickman* stickman, const QString& backgroundLocation, int screenVelcoity, const QString& musicLocation);
    virtual ~Level();

    virtual const QImage& getBackground() const = 0;
    virtual unsigned int getFrameWidth() const = 0;
    virtual unsigned int getFrameHeight() const = 0;
    virtual void moveBackground(QPainter& painter, bool isPaused) = 0;
    virtual void placeStickman(QPainter& painter) = 0;
    virtual void playMusic() = 0;
    virtual void pauseMusic() = 0;
    virtual int getOffset() const = 0;

private:
    int m_offset;
    QImage* m_background;
    int m_screenVelocity;
    Stickman* m_stickman;
    QMediaPlaylist* m_playlist;
    QMediaPlayer* m_music;
    const unsigned int m_frameHeight = 572;
    const unsigned int m_frameWidth = 1487 - 300;
    const unsigned int m_floorBase = 40;
};

#endif // LEVEL_H
