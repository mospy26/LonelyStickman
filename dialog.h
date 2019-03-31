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
#include <iostream>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget* parent = nullptr);
//    Dialog(const QJsonObject* parser, QWidget* parent = nullptr);
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

public slots:
    /**
     * @brief nextFrame
     * Updates the frame
     */
    void nextFrame();

protected:
    /**
     * @brief paintEvent
     * @param event
     * To paint images on screen
     */
    void paintEvent(QPaintEvent* event) override;

//    /**
//     * @brief parse
//     * @param parser
//     * To parse the config file and do error checking
//     */
//    void parse(const QJsonObject& parser);

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
    bool m_pause = false; //Stores if the game is paused or not
};

#endif // DIALOG_H
