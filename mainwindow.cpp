#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sw = new SettingsWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sw;
}

void MainWindow::on_actionSettings_triggered()
{
    sw->show();
}
