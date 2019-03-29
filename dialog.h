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
    explicit Dialog(const QJsonObject* parser, QWidget* parent = nullptr);
    explicit Dialog(Level* level, const QString& configFilePath, QWidget* parent = nullptr);

    Dialog& operator =(Dialog&& dialog);
    ~Dialog() override;

public slots:
    void nextFrame();

protected:
    void paintEvent(QPaintEvent* event) override;
    void parse(const QJsonObject& parser);
    void keyPressEvent(QKeyEvent* event) override;
    void launchConfigMenu();

private:
    //Ui::Dialog* ui;
    Level* m_level;
    QTimer* m_timer;
    QLabel* m_pauseLabel;
    QString m_configFilePath;
    bool m_pause = false;
};

#endif // DIALOG_H
