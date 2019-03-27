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
    explicit Dialog(const QJsonObject* parser, QWidget* parent = nullptr);
    explicit Dialog(Level* level, QWidget* parent = nullptr);

    Dialog& operator =(Dialog&& dialog);
    ~Dialog();

public slots:
    void nextFrame();

protected:
    void paintEvent(QPaintEvent* event) override;
    void parse(const QJsonObject& parser);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void launchConfigMenu();

private:
    //Ui::Dialog* ui;
    Level* m_level;
    QTimer* m_timer;
    QLabel* m_pauseLabel;
    //NewConfiguration m_configMenu;
    bool m_pause = false;
};

#endif // DIALOG_H
