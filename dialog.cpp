#include "dialog.h"
#include "ui_dialog.h"

bool moveRight = false;
bool moveLeft = false;
bool moveUp = false;

Dialog::Dialog(QWidget* parent) {}
    //: ui(new Ui::Dialog) {}

Dialog::Dialog(const QJsonObject* parser, QWidget *parent)
    : QDialog(parent),
      /* ui(new Ui::Dialog), */
      m_timer(new QTimer(this)),
      m_pauseLabel(new QLabel("Paused", this))
{
    parse(*parser);
    //ui->setupUi(this);
    update();
    setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    m_timer->start(32);
    m_level->playMusic();
    m_pauseLabel->hide();
    m_pauseLabel->setText("<font color='red'>PAUSED</font>");
}

Dialog::Dialog(Level* level, QWidget* parent)
    : QDialog(parent),
      /* ui(new Ui::Dialog), */
      m_level(new Level()),
      m_timer(new QTimer(this)),
      m_pauseLabel(new QLabel("Paused", this))
{
    *m_level = std::move(*level);
    //ui->setupUi(this);
    update();
    setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    m_timer->start(32);
    m_level->playMusic();
    m_pauseLabel->hide();
    m_pauseLabel->setText("<font color='red'>PAUSED</font>");
}

Dialog& Dialog::operator =(Dialog&& dialog)
{
    //this->ui = dialog.ui;
    this->m_level = dialog.m_level;
    this->m_timer = dialog.m_timer;
    this->m_pauseLabel = dialog.m_pauseLabel;
    this->m_pause = dialog.m_pause;
    //dialog.ui = nullptr;
    dialog.m_level = nullptr;
    dialog.m_timer = nullptr;
    dialog.m_pauseLabel = nullptr;
    return *this;
}

Dialog::~Dialog()
{
    //delete ui;
    delete m_level;
    delete m_timer;
    delete m_pauseLabel;
}

void Dialog::nextFrame()
{
    update();
}

void Dialog::paintEvent(QPaintEvent* event)
{

    //background = background.scaled(FRAME_WIDTH, FRAME_HEIGHT, Qt::IgnoreAspectRatio);
    QPainter painter(this);
    m_level->moveBackground(painter, m_pause);
    m_level->placeStickman(painter, moveUp, moveRight, moveLeft, m_pause);
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
    if(event->key() == Qt::Key_Escape and !m_pause) m_pause = true;
    else if(event->key() == Qt::Key_Escape and m_pause) m_pause = false;
    if(!m_pause && !m_timer->isActive()) {
        m_pauseLabel->hide();
        m_timer->start(32);
        m_level->playMusic();
    }
    else if(m_pause && m_timer->isActive()) {
        m_timer->stop();
        m_pauseLabel->setGeometry(m_level->getFrameWidth()/2 - 150, m_level->getFrameHeight()/2 - 100, 400, 400);
        m_pauseLabel->show();
        m_level->pauseMusic();
    }
}

//void Dialog::launchConfigMenu()
//{
//    m_configMenu->show();
//}

void Dialog::closeEvent(QCloseEvent *event)
{
//    delete ui;
//    delete m_level;
//    delete m_timer;
//    delete m_pauseLabel;
//    delete this;
//   QWidget::closeEvent(event);
}
