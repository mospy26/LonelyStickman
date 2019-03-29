#ifndef MARIOSTICKMAN_H
#define MARIOSTICKMAN_H

#include "stickman.h"

class MarioStickman : public Stickman
{
public:
    MarioStickman();
    MarioStickman(enum SizeType size, int X, int Y = 0);
    ~MarioStickman() override;

    MarioStickman(MarioStickman&& other);
    MarioStickman& operator =(MarioStickman&& other);

    const QImage& getImage() const override;
    unsigned int getImageHeight() const override;
    unsigned int getXPosition() const override;
    unsigned int getYPosition() const override;
    void setXPosition(unsigned int position) override;
    void setYPosition(unsigned int position) override;

private:
    unsigned int m_size;
    unsigned int m_imageHeight;
    QImage* m_image;
    unsigned int m_X;
    unsigned int m_Y;
};


#endif // MARIOSTICKMAN_H
