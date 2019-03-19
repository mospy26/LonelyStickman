#ifndef SAVEFORM_H
#define SAVEFORM_H

#include <QDialog>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QTextStream>
#include <string>

class SaveForm : public QDialog
{
    Q_OBJECT
public:
    SaveForm(QWidget* parent = nullptr);
    ~SaveForm();
    void loadObjects();
    bool isValidInput(); //check for invalid properties in config file

public slots:
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

    QLineEdit* m_sizeEdit;
    QLineEdit* m_initialXEdit;
    QLineEdit* m_initialVelocityEdit;
    QLineEdit* m_backgroundEdit;
    QLineEdit* m_musicEdit;

    QPushButton* m_saveAs;
};

#endif // SAVEFORM_H
