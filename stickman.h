#ifndef STICKMAN_H
#define STICKMAN_H

#include <QImage>
#include <QDir>
#include <QString>

/**
 * @brief The SizeType enum
 * For storing size types like tiny, normal, large, giant
 */
enum SizeType
{
    TINY = 0,
    NORMAL = 1,
    LARGE = 2,
    GIANT = 3
};

/**
 * @brief The Stickman class
 */
class Stickman
{
public:
    /**
     * @brief Stickman
     * Default Constructor
     */
    Stickman() = default;

    /**
     * @brief Stickman
     * @param size
     * @param X
     * @param Y
     * Constructs a stickman with given size, initial X and initial Y position
     */
    Stickman(enum SizeType size, int X, int Y = 0);

    /**
     * @brief operator =
     * @param other
     * @return the current stickman object to which the contents are moved to
     * Move assignment operator to move contents from one stickman object to another
     */
    Stickman& operator =(Stickman&& other);

    ~Stickman();

    /**
     * @brief getImage
     * @return reference to image representing the stickman
     */
    const QImage& getImage() const;

    /**
     * @brief getImageHeight
     * @return current image height
     */
    unsigned int getImageHeight() const;

    /**
     * @brief getXPosition
     * @return current X position of the stickman
     */
    unsigned int getXPosition() const;

    /**
     * @brief getYPosition
     * @return current Y position of the stickman
     */
    unsigned int getYPosition() const;

    /**
     * @brief setXPosition
     * @param position
     * Setter for X position of the stickman
     */
    void setXPosition(unsigned int position);

    /**
     * @brief setYPosition
     * @param position
     * Setter for the Y position of the stickman
     */
    void setYPosition(unsigned int position);

private:
    unsigned int m_size;
    unsigned int m_imageHeight; //image height of the stickman
    QImage* m_image;
    unsigned int m_X;
    unsigned int m_Y;
};

#endif //STICKMAN_H
