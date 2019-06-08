#ifndef DIALOG_H
#define DIALOG_H

#include "level.h"

#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QTimer>
#include <QPolygon>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget* parent = nullptr);

    /**
     * @brief Dialog
     * @param level
     * @param configFilePath
     * @param parent
     * Constructor that sets the level, config file path and parent of this QWidget.
     */
    Dialog(Level* level, const QString& configFilePath, QWidget* parent = nullptr);

    /**
     * @brief operator =
     * @param dialog
     * @return reference to the object that stores the moved content
     * Move assignment operator to move contents from one dialog to another
     */
    Dialog& operator =(Dialog&& dialog);

    ~Dialog() override;

protected:
    /**
     * @brief paintEvent
     * @param event
     * To paint images on screen
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief keyPressEvent
     * @param event
     * Event that handles the key pressing
     */
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::Dialog* ui;
    Level* m_level; //Stores the level for the game
    QTimer* m_timer; //Timer for updating the screen
    QLabel* m_pauseLabel; //Pause Label
    QString m_configFilePath;
    bool m_isPaused = false; //True if the game is paused
};

#endif // DIALOG_H
