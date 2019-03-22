#include "newconfiguration.h"

NewConfiguration::NewConfiguration(QWidget *parent)
    : m_successLoad(new QLabel("", this)),
      m_loadConfiguration(new QPushButton("Load Game", this)),
      m_saveConfiguration(new QPushButton("Save Game", this)),
      m_playButton(new QPushButton("Play", this)),
      m_parser()
{
    m_playButton->hide(); //hide until loaded config file successfully

    setFixedSize(1000, 700);
    setWindowTitle("Lonely Stickman");

    loadObjects(); //load all buttons

    connect(m_loadConfiguration, SIGNAL(released()), this, SLOT(clickedLoadConfiguration()));
    connect(m_saveConfiguration, SIGNAL(released()), this, SLOT(clickedSaveConfiguration()));
}

NewConfiguration::~NewConfiguration()
{
    delete m_successLoad;
    delete m_loadConfiguration;
    delete m_saveConfiguration;
    delete m_playButton;
    delete m_game;
    delete m_saveDialog;
}

void NewConfiguration::loadObjects()
{
    //tooltips
    m_loadConfiguration->setToolTip("Load a game configuration");
    m_saveConfiguration->setToolTip("Save a game configuration");

    //place buttons
    m_loadConfiguration->setGeometry(400, 400, 200, 80);
    m_loadConfiguration->setText("Load configuration");
    m_saveConfiguration->setGeometry(400, 500, 200, 80);
    m_saveConfiguration->setText("Save configuration");
}

void NewConfiguration::clickedLoadConfiguration()
{

    QDir path = QDir::currentPath();
    path.cd("../../../../LonelyStickman");

    QString loadState = QFileDialog::getOpenFileName(this,
                            tr("Load Game Configuration"), path.absolutePath(),
                            tr("JSON (*.json)"));
    if(loadState.isEmpty())
        return;
    else {
        QFile file(loadState);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }
        try {
            m_parser = parseConfigFile(file.fileName());
        } catch(const char* error) {
            std::cout << error << std::endl;
            m_successLoad->setGeometry(420, 350, 200, 50);
            m_successLoad->setText("<font color='red'>Cannot load config file </font>");
            return;
        }
        setPlayButton();
        connect(m_playButton, SIGNAL(released()), this, SLOT(play()));
    }
}

void NewConfiguration::clickedSaveConfiguration()
{
    m_saveDialog = new SaveForm(this);
    m_saveDialog->show();
}

void NewConfiguration::setPlayButton()
{
   m_playButton->show();
   m_playButton->setToolTip("Play Game");
   m_playButton->setGeometry(400, 250, 200, 80);

   m_successLoad->setGeometry(420, 350, 200, 50);
   m_successLoad->setText("<font color='green'>Loaded Config Successfully</font>");
}

QJsonObject NewConfiguration::parseConfigFile(const QString &filepath)
{
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);

    QJsonDocument configFile(QJsonDocument::fromJson(file.readAll()));
    file.close();
    QJsonObject parser = configFile.object();

    if(parser["size"].toString() == nullptr || (parser["size"].toString() != "tiny"
                                                && parser["size"].toString() != "normal"
                                                && parser["size"].toString() != "large"
                                                && parser["size"].toString() != "giant"))
        throw "size not stated";
    if(parser["initialX"].toString() == nullptr || parser["initialX"].toString() == "")
        throw "initialX not stated";
    if(parser["initialVelocity"].toString() == nullptr || parser["initialVelocity"].toString()  == "")
        throw "initial velocity not stated";
    if(parser["background"].toString() == nullptr || parser["background"].toString() == "")
        throw "background not stated";
    if(parser["music"].toString() == nullptr || parser["music"].toString() == "")
        throw "music not stated";

    if(parser["size"] == "---")
        throw "size not chosen!";

    return parser;
}

void NewConfiguration::play()
{
    this->close();
    m_game = new Dialog(m_parser, nullptr);
    m_game->show();
}
