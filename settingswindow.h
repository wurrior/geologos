#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Settings;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();
    void showAndRefresh();

private slots:
    void on_buttonBox_accepted();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Settings *ui;
    QSettings *settings;
};

#endif // SETTINGSWINDOW_H
