#ifndef NEWCONFIGURATION_H
#define NEWCONFIGURATION_H


#include "dialog.h"
#include "saveform.h"
#include "mario.h"
#include "mariocreator.h"

#include <QDialog>
#include <QLabel>
#include <QMessageBox>

class NewConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit NewConfiguration(QWidget *parent = nullptr);
    ~NewConfiguration();
    void loadObjects();
    void setPlayButton();
    void parseConfigFile(const QString& filepath);
    void closeEvent(QCloseEvent* event) override;

public slots:
    void clickedLoadConfiguration();
    void clickedSaveConfiguration();
    void play();

private:
    QLabel* m_successLoad;

    QPushButton* m_playButton;
    QPushButton* m_loadConfiguration;
    QPushButton* m_saveConfiguration;

    QJsonObject* m_parser;

    SaveForm* m_saveDialog;
    Dialog* m_game;
};

#endif // NEWCONFIGURATION_H
