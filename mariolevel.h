#ifndef MARIOLEVEL_H
#define MARIOLEVEL_H

#include "level.h"

class MarioLevel
{
public:
//  MarioLevel(const QString& backgroundLocation, SizeType size, int initialX, int screenVelocity, const QString& musicLocation);
    MarioLevel(Stickman* stickman, const QString& backgroundLocation, int screenVelcoity, const QString& musicLocation);

    ~MarioLevel();

    MarioLevel(MarioLevel&& other);

    MarioLevel& operator =(MarioLevel&& other);

    const QImage& getBackground() const;
    unsigned int getFrameWidth() const;
    unsigned int getFrameHeight() const;
    void moveBackground(QPainter& painter, bool isPaused);
    void placeStickman(QPainter& painter);
    void playMusic();
    void pauseMusic();
    int getOffset() const;

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

#endif // MARIOLEVEL_H
