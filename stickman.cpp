#include "stickman.h"

Stickman::Stickman(enum SizeType size, int X, int Y)
    : m_size(size), m_imageHeight(0), m_image(nullptr), m_X(X), m_Y(Y)
{
    std::string file;
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
    m_image = new QImage(imagePath.path().append("/").append(file.c_str()));
}

Stickman::Stickman(Stickman&& other)
    : m_size(other.m_size),
      m_imageHeight(other.m_imageHeight),
      m_image(other.m_image),
      m_X(other.m_X),
      m_Y(other.m_Y)
{
    other.m_image = nullptr;
}

Stickman& Stickman::operator =(Stickman&& other)
{
    m_size = other.m_size;
    m_imageHeight = other.m_imageHeight;
    m_image = other.m_image;
    m_X = other.m_X;
    m_Y = other.m_Y;
    other.m_image = nullptr;
    return *this;
}

Stickman::~Stickman() {}

const QImage& Stickman::getImage() const
{
    return *m_image;
}

unsigned int Stickman::getImageHeight() const
{
    return this->m_imageHeight;
}

unsigned int Stickman::getXPosition() const
{
    return this->m_X;
}

unsigned int Stickman::getYPosition() const
{
    return this->m_Y;
}

void Stickman::setXPosition(unsigned int position)
{
    this->m_X = position;
}

void Stickman::setYPosition(unsigned int position)
{
    this->m_Y = position;
}
