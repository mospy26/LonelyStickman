#include "newconfiguration.h"
#include <memory>
NewConfiguration::NewConfiguration(QWidget *parent)
    : QDialog(parent),
      m_mainLabel(new QLabel(this)),
      m_successLoad(new QLabel(this)),
      m_playButton(new QPushButton("Play", this)),
      m_loadConfiguration(new QPushButton("Load Game", this)),
      m_saveConfiguration(new QPushButton("Save Game", this)),
      m_parser(),
      m_configFilePath(),
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
    delete m_saveDialog;
    delete m_parser;
}

void NewConfiguration::loadObjects()
{
    //Main menu text
    QFont font("Arial", 40, QFont::Bold);
    m_mainLabel->setFont(font);
    m_mainLabel->setText("Stickman Game");
    m_mainLabel->setGeometry(350, 100, 300, 100);

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
    m_configFilePath = loadState;

    if(loadState.isEmpty())
        return;
    else {
        QFile file(loadState);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }

        //Check validity
        try {
            parseConfigFile(file.fileName());
        } catch(const char* error) {
            std::unique_ptr<QMessageBox> errorBox = std::make_unique<QMessageBox>(this);
            errorBox->setWindowTitle("Error");
            errorBox->setText(error);
            errorBox->setIcon(QMessageBox::Warning);
            errorBox->exec();
            m_successLoad->setGeometry(420, 350, 200, 50);
            m_successLoad->setText("<font color='red'>Cannot load config file </font>");
            m_playButton->hide();
            return;
        }

        //Set play button if everything is good
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

    if(configFile.isNull()) {
        throw "Error in JSON file! (Check missing braces or key/value pairs?)";
    }

    file.close();
    m_parser = new QJsonObject(configFile.object());

    if(!m_parser->contains("size") ||
            !m_parser->contains("initialX") ||
            !m_parser->contains("initialVelocity") ||
            !m_parser->contains("background") ||
            !m_parser->contains("music"))
        throw "Invalid config file - Missing configurations";

    //Check if initial X and initial Velocity can be parsed to integers
    bool ok = true;
    (*m_parser)["initialX"].toString().toInt(&ok);
    if(!ok) throw "Initial X is not an integer";

    ok = true;
    (*m_parser)["initialVelocity"].toString().toInt(&ok);
    if(!ok) throw "Initial Velocity is not integer";

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
    //Builder and director creates the level
    Mario mario(*m_parser);
    MarioCreator marioCreator(&mario);
    Level* level = marioCreator.create();
    m_game = new Dialog(level, m_configFilePath);
    m_game->setAttribute(Qt::WA_DeleteOnClose, true);
    m_game->show();
    this->close();
}
