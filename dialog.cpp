#include "dialog.h"
#include "ui_dialog.h"

bool moveRight = false;
bool moveLeft = false;
bool moveUp = false;

Dialog::Dialog(const QString& configFilePath, QWidget *parent)
    : ui(new Ui::Dialog)
{
    try {
        parseConfigFile(configFilePath);
    } catch(const char* error) {
        std::cout << error << std::endl;
        exit(EXIT_FAILURE);
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

    if(parser["size"].toString() == nullptr || parser["size"].toString() == "")
        throw "size not stated";
    if(parser["initialX"].toString() == nullptr || parser["initialX"].toString() == "")
        throw "initialX not stated";
    if(parser["initialVelocity"].toString() == nullptr || parser["initialVelocity"].toString()  == "")
        throw "initial velocity not stated";
    if(parser["background"].toString() == nullptr || parser["background"].toString() == "")
        throw "background not stated";
    if(parser["music"].toString() == nullptr || parser["music"].toString() == "")
        throw "music not stated";

    //convert string to size
    SizeType stickmanSize;
    if(parser["size"].toString() == "tiny")     stickmanSize = SizeType::TINY;
    else if(parser["size"].toString() == "normal")   stickmanSize = SizeType::NORMAL;
    else if(parser["size"].toString() == "large")    stickmanSize = SizeType::LARGE;
    else if(parser["size"].toString() == "giant")    stickmanSize = SizeType::GIANT;
    else throw "Size is invalid";

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
