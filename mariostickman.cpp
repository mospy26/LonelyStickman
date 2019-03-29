#include "mariostickman.h"

MarioStickman::MarioStickman() // default size is tiny
    : m_size(SizeType::TINY), m_imageHeight(9999 /* 34 */), m_X(5), m_Y(5) {}

MarioStickman::MarioStickman(enum SizeType size, int X, int Y)
    : m_size(size), m_imageHeight(0), m_image(nullptr), m_X(X), m_Y(Y)
{
    QString file;
    switch (size) {
        case SizeType::TINY:
            file = "mario_tiny.png";
            this->m_imageHeight = 34;
            break;
        case SizeType::NORMAL:
            file = "mario_normal.png";
            this->m_imageHeight = 56;
            break;
        case SizeType::LARGE:
            file = "mario_large.png";
            this->m_imageHeight = 83;
            break;
        case SizeType::GIANT:
            file = "mario_giant.png";
            this->m_imageHeight = 109;
            break;
    }
    QDir imagePath = QDir::currentPath();
    imagePath.cd("../../../../LonelyStickman/img");
    m_image = new QImage(imagePath.path().append("/").append(file));
}

MarioStickman::MarioStickman(MarioStickman&& other)
    : m_size(other.m_size),
      m_imageHeight(other.m_imageHeight),
      m_image(other.m_image),
      m_X(other.m_X),
      m_Y(other.m_Y)
{
    other.m_image = nullptr;
}

MarioStickman& MarioStickman::operator =(MarioStickman&& other)
{
    m_size = other.m_size;
    m_imageHeight = other.m_imageHeight;
    m_image = other.m_image;
    m_X = other.m_X;
    m_Y = other.m_Y;
    other.m_image = nullptr;
    return *this;
}

MarioStickman::~MarioStickman() {}

const QImage& MarioStickman::getImage() const
{
    return *m_image;
}

unsigned int MarioStickman::getImageHeight() const
{
    return this->m_imageHeight;
}

unsigned int MarioStickman::getXPosition() const
{
    return this->m_X;
}

unsigned int MarioStickman::getYPosition() const
{
    return this->m_Y;
}

void MarioStickman::setXPosition(unsigned int position)
{
    this->m_X = position;
}

void MarioStickman::setYPosition(unsigned int position)
{
    this->m_Y = position;
}
