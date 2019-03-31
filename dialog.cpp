#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget* parent)
    : ui(new Ui::Dialog) {}

//Dialog::Dialog(const QJsonObject* parser, QWidget *parent)
//    : QDialog(parent),
//      ui(new Ui::Dialog),
//      m_timer(new QTimer(this)),
//      m_pauseLabel(new QLabel("Paused", this))
//{
//    //parse(*parser);
//    ui->setupUi(this);
//    update();
//    setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
//    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame())); //update the frame
//    m_timer->start(32);
//    m_level->playMusic();
//    m_pauseLabel->hide(); //Hide the Pause label until game is paused
//    m_pauseLabel->setText("<font color='red'>PAUSED</font>");
//}

Dialog::Dialog(Level* level, const QString& configFilePath, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::Dialog),
      m_level(new Level()),
      m_timer(new QTimer(this)),
      m_pauseLabel(new QLabel("Paused", this)),
      m_configFilePath(configFilePath)
{
    *m_level = std::move(*level);
    ui->setupUi(this);
    update();
    setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update())); //call the next frame
    m_timer->start(32);
    m_level->playMusic();
    m_pauseLabel->hide();
}

Dialog& Dialog::operator =(Dialog&& dialog)
{
    this->ui = dialog.ui;
    this->m_level = dialog.m_level;
    this->m_timer = dialog.m_timer;
    this->m_pauseLabel = dialog.m_pauseLabel;
    this->m_isPaused = dialog.m_isPaused;
    dialog.ui = nullptr;
    dialog.m_level = nullptr;
    dialog.m_timer = nullptr;
    dialog.m_pauseLabel = nullptr;
    return *this;
}

Dialog::~Dialog()
{
    delete ui;
    delete m_level;
    delete m_timer;
    delete m_pauseLabel;
}

void Dialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    m_level->moveBackground(painter, m_isPaused);
    m_level->placeStickman(painter);
}

//void Dialog::parse(const QJsonObject& parser)
//{
//    //convert string to size
//    SizeType stickmanSize;
//    if(parser["size"].toString() == "tiny")     stickmanSize = SizeType::TINY;
//    else if(parser["size"].toString() == "normal")   stickmanSize = SizeType::NORMAL;
//    else if(parser["size"].toString() == "large")    stickmanSize = SizeType::LARGE;
//    else stickmanSize = SizeType::GIANT;

//    //construct the level using the config file's configuration
//    m_level = new Level(parser["background"].toString(),
//                            stickmanSize,
//                            parser["initialX"].toString().toInt(),
//                            parser["initialVelocity"].toString().toInt(),
//                            parser["music"].toString());
//}

void Dialog::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape and !m_isPaused) m_isPaused = true;
    else if(event->key() == Qt::Key_Escape and m_isPaused) m_isPaused = false;

    //restart the timer if not paused and the game was not active earlier
    if(!m_isPaused && !m_timer->isActive()) {
        m_pauseLabel->hide();
        m_timer->start(32);
        m_level->playMusic();
    }

    //stop the timer if paused and the game was active earlier
    else if(m_isPaused && m_timer->isActive()) {
        m_timer->stop();
        m_pauseLabel->setText("<font color='red'; size='30'>PAUSED</font>");
        m_pauseLabel->setGeometry(m_level->getFrameWidth()/2 - 50, 0, 400, 50);
        m_pauseLabel->show();
        m_level->pauseMusic();
    }
}
