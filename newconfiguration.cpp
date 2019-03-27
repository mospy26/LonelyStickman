#include "newconfiguration.h"

NewConfiguration::NewConfiguration(QWidget *parent)
    : QDialog(parent),
      m_successLoad(new QLabel(this)),
      m_playButton(new QPushButton("Play", this)),
      m_loadConfiguration(new QPushButton("Load Game", this)),
      m_saveConfiguration(new QPushButton("Save Game", this)),
      m_parser(),
      m_saveDialog()
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
    //delete m_game;
    delete m_saveDialog;
    delete m_parser;
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
            parseConfigFile(file.fileName());
        } catch(const char* error) {
            std::cout << error << std::endl;
            m_successLoad->setGeometry(420, 350, 200, 50);
            m_successLoad->setText("<font color='red'>Cannot load config file </font>");
            m_playButton->hide();
            return;
        }
        setPlayButton();
        connect(&(*m_playButton), SIGNAL(released()), this, SLOT(play()));
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

void NewConfiguration::parseConfigFile(const QString &filepath)
{
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);

    QJsonDocument configFile(QJsonDocument::fromJson(file.readAll()));
    file.close();
    m_parser = new QJsonObject(configFile.object());

    if((*m_parser)["size"].toString() == nullptr || ((*m_parser)["size"].toString() != "tiny"
                                                && (*m_parser)["size"].toString() != "normal"
                                                && (*m_parser)["size"].toString() != "large"
                                                && (*m_parser)["size"].toString() != "giant"))
        throw "size not stated";
    if((*m_parser)["initialX"].toString() == nullptr || (*m_parser)["initialX"].toString() == "")
        throw "initialX not stated";
    if((*m_parser)["initialVelocity"].toString() == nullptr || (*m_parser)["initialVelocity"].toString()  == "")
        throw "initial velocity not stated";
    if((*m_parser)["background"].toString() == nullptr || (*m_parser)["background"].toString() == "")
        throw "background not stated";
    if((*m_parser)["music"].toString() == nullptr || (*m_parser)["music"].toString() == "")
        throw "music not stated";

    if((*m_parser)["size"] == "---")
        throw "size not chosen!";

}

void NewConfiguration::play()
{
    Mario mario(*m_parser);
    MarioCreator marioCreator(&mario);
    Level* level = marioCreator.create();
    m_game = new Dialog(level);
    m_game->setAttribute(Qt::WA_DeleteOnClose, true);
    m_game->show();
    this->close();
}

void NewConfiguration::closeEvent(QCloseEvent* event)
{
//    delete m_successLoad;
//    delete m_loadConfiguration;
//    delete m_saveConfiguration;
//    delete m_playButton;
//    delete m_saveDialog;
//    delete m_parser;
//    QWidget::closeEvent(event);
}
