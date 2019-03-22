#ifndef DIALOG_H
#define DIALOG_H

#include "level.h"

#include <QDialog>
#include <QFile>
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
    explicit Dialog(const QJsonObject* parser, QWidget* parent = nullptr);
    explicit Dialog(Level& level, QWidget* parent = nullptr);
    ~Dialog();

public slots:
    void nextFrame();

protected:
    void paintEvent(QPaintEvent* event);
    void parse(const QJsonObject& parser);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    Ui::Dialog *ui;
    Level* m_level;
};

#endif // DIALOG_H
