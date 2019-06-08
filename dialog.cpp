#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget* parent)
    : ui(new Ui::Dialog) {}

Dialog::Dialog(Level* level, const QString& configFilePath, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::Dialog),
      m_level(new Level()),
      m_timer(new QTimer(this)),
      m_pauseLabel(new QLabel("Paused", this)),
      m_configFilePath(configFilePath)
{
    //Move the contents of supplied level to current level
    *m_level = std::move(*level);
    ui->setupUi(this);
    update();
    setFixedSize(this->m_level->getFrameWidth(), this->m_level->getFrameHeight());
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update())); //call the next frame
    m_timer->start(32);
    m_level->playMusic();
    m_pauseLabel->hide(); //Hide pause label until escape button is pressed
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
