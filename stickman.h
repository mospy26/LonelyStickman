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

    virtual ~Stickman() {}

    virtual const QImage& getImage() const = 0;
    virtual unsigned int getImageHeight() const = 0;
    virtual unsigned int getXPosition() const = 0;
    virtual unsigned int getYPosition() const = 0;
    virtual void setXPosition(unsigned int position) = 0;
    virtual void setYPosition(unsigned int position) = 0;
};

#endif //STICKMAN_H
