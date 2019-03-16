#include "dialog.h"
#include "ui_dialog.h"

#include <QImage>
#include <QPainter>
#include <QPolygon>
#include <QKeyEvent>

bool moveRight = false;
bool moveLeft = false;
bool moveUp = false;
int offset = 0;
const int screenVelocity = 10;

Dialog::Dialog(QWidget *parent)
    : ui(new Ui::Dialog),
      m_level(new Level())
{
    ui->setupUi(this);
    this->update();
    this->setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(32);
    this->m_level->playMusic();
}

Dialog::Dialog(const std::string& background, const std::string& size, const std::string& music, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Dialog)
{
    //convert string to size
    SizeType stickmanSize;
    if(size == "tiny") stickmanSize = SizeType::TINY;
    if(size == "normal") stickmanSize = SizeType::NORMAL;
    if(size == "large") stickmanSize = SizeType::LARGE;
    if(size == "giant") stickmanSize = SizeType::GIANT;

    m_level = new Level(background, stickmanSize, music);

    ui->setupUi(this);
    this->update();
    this->setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(32);
    this->m_level->playMusic();
}

Dialog::~Dialog()
{
    delete ui;
    delete m_level;
}

void Dialog::nextFrame()
{
    this->update();
}

void Dialog::paintEvent(QPaintEvent* event)
{

    //background = background.scaled(FRAME_WIDTH, FRAME_HEIGHT, Qt::KeepAspectRatio);

    QPainter painter(this);

    scroll();

    painter.drawImage(offset, 0, this->m_level->getBackground(), 0, 0, this->m_level->getFrameWidth(), this->m_level->getFrameHeight());

    painter.drawImage(this->m_level->getFrameWidth() + offset, 0, this->m_level->getBackground(), 0, 0, this->m_level->getFrameWidth(), this->m_level->getFrameHeight());

    if(offset <= -this->m_level->getFrameWidth())
        offset = 0;

    this->m_level->getStickman().movePlayer(moveUp, moveRight, moveLeft,
                                            m_level->getFrameHeight() -
                                            m_level->getFloorBase() -
                                            m_level->getStickman().getImageHeight());

    painter.drawImage(this->m_level->getStickman().getXPosition(),
                      this->m_level->getStickman().getYPosition(),
                      this->m_level->getStickman().getImage());
}

void Dialog::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
        moveRight = false;
    if(event->key() == Qt::Key_Left)
        moveLeft = false;
    if(event->key() == Qt::Key_Up)
        moveUp = false;
}

void Dialog::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Right)
        moveRight = true;
    if(event->key() == Qt::Key_Left)
        moveLeft = true;
    if(event->key() == Qt::Key_Up)
        moveUp = true;
}

void Dialog::scroll()
{
    offset -= screenVelocity;
}
