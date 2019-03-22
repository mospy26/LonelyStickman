#include "dialog.h"
#include "ui_dialog.h"

bool moveRight = false;
bool moveLeft = false;
bool moveUp = false;

Dialog::Dialog(const QJsonObject& parser, QWidget *parent)
    : ui(new Ui::Dialog)
{
    parse(parser);
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

    //background = background.scaled(FRAME_WIDTH, FRAME_HEIGHT, Qt::IgnoreAspectRatio);

    QPainter painter(this);

    m_level->moveBackground(painter);
    m_level->placeStickman(painter, moveUp, moveRight, moveLeft);
}

void Dialog::parse(const QJsonObject& parser)
{
    //convert string to size
    SizeType stickmanSize;
    if(parser["size"].toString() == "tiny")     stickmanSize = SizeType::TINY;
    else if(parser["size"].toString() == "normal")   stickmanSize = SizeType::NORMAL;
    else if(parser["size"].toString() == "large")    stickmanSize = SizeType::LARGE;
    else stickmanSize = SizeType::GIANT;

    m_level = new Level(parser["background"].toString(),
                            stickmanSize,
                            parser["initialX"].toString().toInt(),
                            parser["initialVelocity"].toString().toInt(),
                            parser["music"].toString());
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
