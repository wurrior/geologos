#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QCloseEvent>
#include "settingswindow.h"
#include "newmeasurement.h"
#include "control.h"
#include <QtConcurrentRun>

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
    void toggleAdvancedControls(bool active);
    void toggleControls(bool active);
    void setMeasurement(Measurement * meas);

public slots:
    void updateCanvas();

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

    void on_actionNew_triggered();

    void on_actionBackwards_triggered();

    void on_actionForwards_triggered();

private:
    Ui::MainWindow *ui;
    SettingsWindow *sw;
    NewMeasurement *nm;
    Control *control;
    Measurement * m;
};

#endif // MAINWINDOW_H
