#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "settingswindow.h"
#include "control.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeSettings();
    void readSettings();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();

    void on_actionStop_triggered();

    void on_actionSave_triggered();

    void on_actionDown_triggered();

    void on_actionUp_triggered();

    void on_actionStep_back_triggered();

    void on_actionCalibrate_triggered();

private:
    Ui::MainWindow *ui;
    SettingsWindow *sw;
    Control *control;

};

#endif // MAINWINDOW_H
