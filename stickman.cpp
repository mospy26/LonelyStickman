#include "stickman.h"

Stickman::Stickman() // default size is tiny
    : m_size(SizeType::TINY), m_imageHeight(34), m_image(QImage(":/img/mario_tiny")), m_X(5), m_Y(5){}

Stickman::Stickman(enum SizeType size, int X, int Y)
    : m_size(size), m_imageHeight(0), m_image(nullptr), m_X(X), m_Y(Y)
{
    std::string file;
    switch (size) {
        case SizeType::TINY:
            file = "mario_tiny";
            this->m_imageHeight = 34;
            break;
        case SizeType::NORMAL:
            file = "mario_normal";
            this->m_imageHeight = 56;
            break;
        case SizeType::LARGE:
            file = "mario_large";
            this->m_imageHeight = 83;
            break;
        case SizeType::GIANT:
            file = "mario_giant";
            this->m_imageHeight = 109;
            break;
    }
    m_image = QImage(QString(":/img/") + QString(file.c_str()));
}

Stickman::~Stickman() {}

const QImage& Stickman::getImage() const
{
    return this->m_image;
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
