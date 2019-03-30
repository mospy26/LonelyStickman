#ifndef SAVEFORM_H
#define SAVEFORM_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QTextStream>
#include <string>

/**
 * @brief The SaveForm class
 * The class for the Save configuration dialog
 */
class SaveForm : public QDialog
{
    Q_OBJECT
public: 
    /**
     * @brief SaveForm
     * @param parent
     * Constructs the save form - initialises all constituents
     */
    explicit SaveForm(QWidget* parent = nullptr);

    ~SaveForm();

    /**
     * @brief loadObjects
     * Presents required contituents like labels and a combo box on the screen
     */
    void loadObjects();

    /**
     * @brief isValidInput
     * @return True if the config file is valid
     * If the config file is valid, i.e. has required configurations then returns True
     */
    bool isValidInput();

    /**
     * @brief hideErrorLabels
     * Hides the error labels which are not supposed to show up
     */
    void hideErrorLabels();

public slots:
    /**
     * @brief saveConfig
     * Handles the event of "Save config file" when input is entered
     */
    void saveConfig();

private:
    QLabel* m_sizeLabel;
    QLabel* m_initialXLabel;
    QLabel* m_initialVelocityLabel;
    QLabel* m_backgroundLabel;
    QLabel* m_musicLabel;

    QLabel* m_sizeError;
    QLabel* m_initialXError;
    QLabel* m_initialVelocityError;
    QLabel* m_backgroundError;
    QLabel* m_musicError;

    QComboBox* m_sizeComboBox; //Combo box for size choice
    QLineEdit* m_initialXEdit;
    QLineEdit* m_initialVelocityEdit;
    QLineEdit* m_backgroundEdit;
    QLineEdit* m_musicEdit;

    QPushButton* m_saveAs; //"Save As" button
};

#endif // SAVEFORM_H
