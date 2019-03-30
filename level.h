#ifndef LEVEL_H
#define LEVEL_H

#include "stickman.h"

#include <QImage>
#include <QPainter>
#include <string>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>

/**
 * @brief The Level class
 */
class Level
{
public:
    /**
     * @brief Level
     * Default Constructor
     */
    Level() = default;

    /**
     * @brief Level
     * @param backgroundLocation
     * @param size
     * @param initialX
     * @param screenVelocity
     * @param musicLocation
     * Constructs a level with background as provided, stickman size as provided, and other properties as given
     */
    Level(const QString& backgroundLocation, SizeType size, int initialX, int screenVelocity, const QString& musicLocation);

    /**
     * @brief Level
     * @param stickman
     * @param backgroundLocation
     * @param screenVelcoity
     * @param musicLocation
     * Constructs the level from the given stickman and background location, screen velocity and music location
     */
    Level(Stickman* stickman, const QString& backgroundLocation, int screenVelcoity, const QString& musicLocation);

    ~Level();

    /**
     * @brief Level
     * @param other
     * Move constructor for Level
     */
    Level(Level&& other);

    /**
     * @brief operator =
     * @param other
     * @return level object to which contents of another level object were moved to
     * Move assignment operator
     */
    Level& operator =(Level&& other);

    /**
     * @brief getBackground
     * @return reference to a QImage representing the background
     */
    const QImage& getBackground() const;

    /**
     * @brief getFrameWidth
     * @return current frame width
     * Getter for frame width
     */
    unsigned int getFrameWidth() const;

    /**
     * @brief getFrameHeight
     * @return current frame height
     * Getter for current frame height
     */
    unsigned int getFrameHeight() const;

    /**
     * @brief moveBackground
     * @param painter
     * @param isPaused
     * Method to move the background with velocity specified by the member variable "m_screenVelcity" based on
     * if the game is paused or not
     */
    void moveBackground(QPainter& painter, bool isPaused);

    /**
     * @brief placeStickman
     * @param painter
     * Method that places the stickman on the screen based off the configuration specified in the config file
     */
    void placeStickman(QPainter& painter);

    /**
     * @brief playMusic
     * Method that plays music in the background
     */
    void playMusic();

    /**
     * @brief pauseMusic
     * Method that pauses the music when the game is paused
     */
    void pauseMusic();

    /**
     * @brief getOffset
     * @return current offset
     * Getter for the offset
     */
    int getOffset() const;

private:
    int m_offset; //offset for the image movement
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
