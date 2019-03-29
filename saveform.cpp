#include "saveform.h"

SaveForm::SaveForm(QWidget* parent)
    : QDialog(parent),
      m_sizeLabel(new QLabel("Size", this)),
      m_initialXLabel(new QLabel("Initial position X", this)),
      m_initialVelocityLabel(new QLabel("Initial velocity", this)),
      m_backgroundLabel(new QLabel("Background", this)),
      m_musicLabel(new QLabel("Music", this)),
      m_sizeError(new QLabel("", this)),
      m_initialXError(new QLabel("", this)),
      m_initialVelocityError(new QLabel("", this)),
      m_backgroundError(new QLabel("", this)),
      m_musicError(new QLabel("", this)),
      m_sizeComboBox(new QComboBox(this)),
      m_initialXEdit(new QLineEdit("", this)),
      m_initialVelocityEdit(new QLineEdit("", this)),
      m_backgroundEdit(new QLineEdit("", this)),
      m_musicEdit(new QLineEdit("", this)),
      m_saveAs(new QPushButton("Save", this))
{
    setFixedSize(800, 600);
    setWindowTitle("Save Config File");

    loadObjects(); //load all buttons

    connect(m_saveAs, SIGNAL(released()), this, SLOT(saveConfig()));
}

SaveForm::~SaveForm()
{
    delete m_sizeLabel;
    delete m_initialXLabel;
    delete m_initialVelocityLabel;
    delete m_backgroundLabel;
    delete m_musicLabel;

    delete m_sizeError;
    delete m_initialXError;
    delete m_initialVelocityError;

    delete m_sizeComboBox;
    delete m_initialXEdit;
    delete m_initialVelocityEdit;
    delete m_backgroundEdit;
    delete m_musicEdit;

    delete m_saveAs;
}

void SaveForm::loadObjects()
{
    m_saveAs->setGeometry(300, 450, 200, 100);

    m_sizeLabel->setGeometry(100, 100, 100, 30);
    m_initialXLabel->setGeometry(100, 130, 100, 30);
    m_initialVelocityLabel->setGeometry(100, 160, 100, 30);
    m_backgroundLabel->setGeometry(100, 190, 100, 30);
    m_musicLabel->setGeometry(100, 220, 100, 30);

    m_sizeError->setGeometry(400, 100, 100, 30);
    m_initialXError->setGeometry(400, 130, 100, 30);
    m_initialVelocityError->setGeometry(400, 160, 100, 30);

    m_sizeComboBox->setGeometry(500, 100, 100, 30);
  
    m_sizeComboBox->addItem("---");
    m_sizeComboBox->addItem("tiny");
    m_sizeComboBox->addItem("normal");
    m_sizeComboBox->addItem("large");
    m_sizeComboBox->addItem("giant");

    m_initialXEdit->setGeometry(500, 130, 100, 30);
    m_initialVelocityEdit->setGeometry(500, 160, 100, 30);
    m_backgroundEdit->setGeometry(500, 190, 100, 30);
    m_musicEdit->setGeometry(500, 220, 100, 30);
}

void SaveForm::hideErrorLabels()
{
    m_sizeError->hide();
    m_initialXError->hide();
    m_initialVelocityError->hide();
}

bool SaveForm::isValidInput()
{
    bool isValid = true;
    if(m_sizeComboBox->currentText() == "---") {
        m_sizeError->setText("<font color='red'>Choose Size!</font>");
        isValid = false;
    }
    else m_sizeError->hide();

    try {
        int data = std::stoi(m_initialXEdit->text().toUtf8().constData());
        if(data < 0 || data > 1187) throw std::invalid_argument("Error");
        else m_initialXError->hide();
    } catch(const std::invalid_argument& error) {
        m_initialXError->setText("<font color='red'>Invalid X Position</font>");
        isValid = false;
    }

    try {
        int data = std::stoi(m_initialVelocityEdit->text().toUtf8().constData());
        if(data < 0) throw std::invalid_argument("Error");
        else m_initialVelocityError->hide();
    } catch(const std::invalid_argument& error) {

        m_initialVelocityError->setText("<font color='red'>Invalid velocity</font>");
        isValid = false;
    }
    return isValid;
}

void SaveForm::saveConfig()
{

    if(!isValidInput()) return;

    QDir path = QDir::currentPath();
    path.cd("../../../../LonelyStickman");

    QJsonObject jsonContent;
    jsonContent.insert("size", QJsonValue::fromVariant(m_sizeComboBox->currentText()));
    jsonContent.insert("initialX", QJsonValue::fromVariant(m_initialXEdit->text()));
    jsonContent.insert("initialVelocity", QJsonValue::fromVariant(m_initialVelocityEdit->text()));
    jsonContent.insert("background", QJsonValue::fromVariant(m_backgroundEdit->text()));
    jsonContent.insert("music", QJsonValue::fromVariant(m_musicEdit->text()));

    QJsonDocument doc(jsonContent);
    QString contents = doc.toJson();

    QString saveState = QFileDialog::getSaveFileName(this,
                            tr("Save Game Configuration"), path.absolutePath(),
                            tr("JSON (*.json"));
    if(saveState.isEmpty())
        return;
    else {
        QFile file(saveState);

        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to store file"),
            file.errorString());
            return;
        }
        QTextStream stream(&file);
        stream << contents;
        this->close();
        return;
    }
}
