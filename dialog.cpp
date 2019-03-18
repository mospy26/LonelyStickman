#include "dialog.h"
#include "ui_dialog.h"

bool moveRight = false;
bool moveLeft = false;
bool moveUp = false;

Dialog::Dialog(QWidget *parent)
    : ui(new Ui::Dialog),
      m_level(new Level())
{
    try {
        parseConfigFile();
    } catch(const char* error) {
        std::cout << error << std::endl;
    }
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

void Dialog::parseConfigFile(QString filepath)
{
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);

    QJsonDocument configFile(QJsonDocument::fromJson(file.readAll()));
    file.close();
    QJsonObject parser = configFile.object();

    std::cout << parser["size"].toString().toUtf8().constData() << std::endl;

    if(parser["size"].toString() == nullptr)            throw "size not stated";
    if(parser["initialX"].toString() == nullptr)        throw "initialX not stated";
    if(parser["initialVelocity"].toString() == nullptr) throw "initial velocity not stated";
    if(parser["background"].toString() == nullptr)      throw "background not stated";
    if(parser["music"].toString() == nullptr)           throw "music not stated";

    //convert string to size
    SizeType stickmanSize;
    if(parser["size"].toString() == "tiny")     stickmanSize = SizeType::TINY;
    if(parser["size"].toString() == "normal")   stickmanSize = SizeType::NORMAL;
    if(parser["size"].toString() == "large")    stickmanSize = SizeType::LARGE;
    if(parser["size"].toString() == "giant")    stickmanSize = SizeType::GIANT;

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
