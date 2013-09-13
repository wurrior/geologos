#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sw = new SettingsWindow(this);
    readSettings();
    control = new Control(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sw;
    delete control;
}

void MainWindow::on_actionSettings_triggered()
{
    sw->showAndRefresh();
}

void MainWindow::writeSettings()
{
    QSettings settings("Stemlux Systems", "Geologos");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("Stemlux Systems", "Geologos");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Geologos v1.0\n\nStemlux Systems Oy\n2013");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void MainWindow::on_actionStop_triggered()
{
    control->stop();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Save Measurement Data"), "",
             tr("Geologos data (*.sgd);;All Files (*)"));
}
