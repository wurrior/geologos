#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m(new Measurement)
{
    ui->setupUi(this);
    sw = new SettingsWindow(this);
    nm = new NewMeasurement(this);
    readSettings();
    control = new Control(this);
    ui->progressBar->hide();
    QObject::connect(control,&Control::measurementStopped,this, &MainWindow::toggleControls);
    QObject::connect(control,&Control::dataReceived,this,&MainWindow::updateCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sw;
    delete nm;
    delete m;
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

void MainWindow::toggleAdvancedControls(bool active)
{
    ui->actionUp->setEnabled(active);
    ui->actionDown->setEnabled(active);
}

void MainWindow::toggleControls(bool active)
{
    ui->actionNew->setEnabled(active);
}

void MainWindow::setMeasurement(Measurement *meas)
{
    delete m;
    m = meas;
    // start measuring:
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum((m->getEnd())-(m->getBegin()));
    ui->progressBar->show();
    QtConcurrent::run(this->control,&Control::measureSample,m);
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
    ui->progressBar->hide();
    updateCanvas();
    control->stop();
}

void MainWindow::on_actionSave_triggered()
{
    QString results = m->toString();
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Save Measurement Data"), "results.csv",
             tr("Geologos data (*.csv);;All Files (*)"));
    QFile filu(fileName);
    filu.open(QIODevice::WriteOnly);

    filu.write(results.toLocal8Bit() ,results.length());
}

void MainWindow::on_actionDown_triggered()
{
    QtConcurrent::run(this->control,&Control::lower);
}

void MainWindow::on_actionUp_triggered()
{
    QtConcurrent::run(this->control,&Control::lift);
}

void MainWindow::on_actionStep_back_triggered()
{
    QtConcurrent::run(this->control,&Control::stepBack);
}

void MainWindow::on_actionCalibrate_triggered()
{
    QtConcurrent::run(this->control,&Control::measurePoint);
}

void MainWindow::on_actionNew_triggered()
{
    nm->show();
}

void MainWindow::updateCanvas()
{
//    // get values:
    QList<int> sval = m->getValues();
    QList<int> aval = m->getAirValues();

// clear canvas:
    ui->widget->clearCanvas();
//    // draw grid:
    ui->widget->drawGrid(sval.size()*m->getInterval());
//    // draw air:
    ui->widget->getPainter()->setPen(QPen(Qt::blue,2));
    ui->widget->drawCurve( &aval, m->getInterval(), m->getBegin());
//    // draw values:
    ui->widget->getPainter()->setPen(QPen(Qt::red,2));
    ui->widget->drawCurve( &sval, m->getInterval(), m->getBegin());
//    // draw difference:
    ui->widget->getPainter()->setPen(QPen(Qt::yellow,2));

    // move progressbar:
    int progress = (aval.size() + sval.size()) * (m->getInterval()/2);
    ui->progressBar->setValue( progress );
    if( progress >= ui->progressBar->maximum() )
        ui->progressBar->hide();
    // redraw everything:
    ui->widget->redraw();
}



void MainWindow::on_actionBackwards_triggered()
{
    QtConcurrent::run(this->control,&Control::backwards);
}

void MainWindow::on_actionForwards_triggered()
{
    QtConcurrent::run(this->control,&Control::forwards);
}
