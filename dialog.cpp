#include "dialog.h"
#include "ui_dialog.h"

bool moveRight = false;
bool moveLeft = false;
bool moveUp = false;

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

Dialog::Dialog(const std::string& background,
                    const std::string& size,
                    const std::string& music,
                    int initialX,
                    int initialVelocity,
                    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Dialog)
{
    //convert string to size
    SizeType stickmanSize;
    if(size == "tiny") stickmanSize = SizeType::TINY;
    if(size == "normal") stickmanSize = SizeType::NORMAL;
    if(size == "large") stickmanSize = SizeType::LARGE;
    if(size == "giant") stickmanSize = SizeType::GIANT;

    m_level = new Level(background, stickmanSize, initialX, initialVelocity,  music);

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

    m_level->moveBackground(painter);
    m_level->placeStickman(painter, moveUp, moveRight, moveLeft);
}

void Dialog::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right) moveRight = false;
    if(event->key() == Qt::Key_Left) moveLeft = false;
    if(event->key() == Qt::Key_Up) moveUp = false;
}

void Dialog::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Right) moveRight = true;
    if(event->key() == Qt::Key_Left) moveLeft = true;
    if(event->key() == Qt::Key_Up) moveUp = true;
}
