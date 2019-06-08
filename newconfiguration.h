#ifndef NEWCONFIGURATION_H
#define NEWCONFIGURATION_H


#include "dialog.h"
#include "saveform.h"
#include "mario.h"
#include "mariocreator.h"

#include <QDialog>
#include <QLabel>
#include <QMessageBox>

/**
 * @brief The NewConfiguration class
 * The class for the main menu
 */
class NewConfiguration : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief NewConfiguration
     * @param parent
     * Constructs the menu
     */
    explicit NewConfiguration(QWidget *parent = nullptr);

    ~NewConfiguration();

    /**
     * @brief loadObjects
     * Loads labels and push buttons that constitute the menu
     */
    void loadObjects();

    /**
     * @brief setPlayButton
     * Method to present the play push button when the config file is loaded
     */
    void setPlayButton();

    /**
     * @brief parseConfigFile
     * @param filepath
     * Method for checking the validithy of the config file and sets the parser
     */
    void parseConfigFile(const QString& filepath);

public slots:
    /**
     * @brief clickedLoadConfiguration
     * Method that handles the event when the "Load" push button is clicked
     */
    void clickedLoadConfiguration();

    /**
     * @brief clickedSaveConfiguration
     * Method that handles the event when the "Save" push button is clicked
     */
    void clickedSaveConfiguration();

    /**
     * @brief play
     * Method that builds the level and loads the game dialog for playing
     */
    void play();

private:
    QLabel* m_mainLabel; //Main menu label "Stickman"
    QLabel* m_successLoad; //Label that appears if the config file was successfully loaded

    QPushButton* m_playButton;
    QPushButton* m_loadConfiguration; //Load button
    QPushButton* m_saveConfiguration; //Save button

    QJsonObject* m_parser;
    QString m_configFilePath;

    SaveForm* m_saveDialog; //Save config dialog
    Dialog* m_game; //Game dialog

};

#endif // NEWCONFIGURATION_H
