#ifndef STICKMAN_H
#define STICKMAN_H

#include <QImage>
#include <QDir>
#include <QString>

enum SizeType
{
    TINY = 0,
    NORMAL = 1,
    LARGE = 2,
    GIANT = 3
};

class Stickman
{
public:
    Stickman();
    Stickman(enum SizeType size, int X, int Y = 0);
    Stickman(Stickman&& other);

    Stickman& operator =(Stickman&& other);

    ~Stickman();

    const QImage& getImage() const;
    unsigned int getImageHeight() const;
    unsigned int getXPosition() const;
    unsigned int getYPosition() const;
    void setXPosition(unsigned int position);
    void setYPosition(unsigned int position);

private:
    unsigned int m_size;
    unsigned int m_imageHeight;
    QImage* m_image;
    unsigned int m_X;
    unsigned int m_Y;
};

#endif //STICKMAN_H
