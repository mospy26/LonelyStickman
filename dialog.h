#ifndef DIALOG_H
#define DIALOG_H

#include "level.h"

#include <QDialog>
#include <QTimer>
#include <QImage>
#include <QPolygon>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    explicit Dialog(const std::string& background,
                        const std::string& size,
                        const std::string& music,
                        int initialX,
                        QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void nextFrame();

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::Dialog *ui;
    Level* m_level;
};

#endif // DIALOG_H
