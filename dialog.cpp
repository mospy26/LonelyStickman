#include "dialog.h"
#include "ui_dialog.h"

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

Dialog::Dialog(Level* level, const QString& configFilePath, QWidget* parent)
    : QDialog(parent),
      /* ui(new Ui::Dialog), */
      m_level(new Level()),
      m_timer(new QTimer(this)),
      m_pauseLabel(new QLabel("Paused", this)),
      m_configFilePath(configFilePath)
{
    *m_level = std::move(*level);
    //ui->setupUi(this);
    update();
    setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    m_timer->start(32);
    m_level->playMusic();
    m_pauseLabel->hide();
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
    QPainter painter(this);
    m_level->moveBackground(painter, m_pause);
    m_level->placeStickman(painter);
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

void Dialog::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape and !m_pause) m_pause = true;
    else if(event->key() == Qt::Key_Escape and m_pause) m_pause = false;
    if(!m_pause && !m_timer->isActive()) {
        m_pauseLabel->hide();
        m_timer->start(32);
        m_level->playMusic();
    }
    else if(m_pause && m_timer->isActive()) {
        m_timer->stop();
        m_pauseLabel->setText("<font color='red'; size='30'>PAUSED</font>");
        m_pauseLabel->setGeometry(m_level->getFrameWidth()/2 - 50, 0, 400, 50);
        m_pauseLabel->show();
        m_level->pauseMusic();
    }
}
