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
    ~Level();

    const QImage& getBackground() const;
    unsigned int getFrameWidth() const;
    unsigned int getFrameHeight() const;
    void moveBackground(QPainter& painter);
    void placeStickman(QPainter& painter, bool moveUp, bool moveRight, bool moveLeft);
    void playMusic();

private:
    QImage m_background;
    int m_screenVelocity;
    Stickman* m_stickman;
    QMediaPlaylist* m_playlist;
    QMediaPlayer* m_music;
    const unsigned int m_frameHeight = 572;
    const unsigned int m_frameWidth = 1487 - 300;
    const unsigned int m_floorBase = 40;
};

#endif // LEVEL_H
