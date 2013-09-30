#include "newmeasurement.h"
#include "ui_newmeasurement.h"
#include "mainwindow.h"
#include "control.h"

NewMeasurement::NewMeasurement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMeasurement),
    m(new Measurement)// empty measurement
{
    ui->setupUi(this);
}

NewMeasurement::~NewMeasurement()
{
    delete ui;
    delete m;
}

void NewMeasurement::on_buttonBox_accepted()
{
    // delete old measurement
    delete m;
    // create new Measurement
    m = new Measurement(
                ui->begin->value(),
                ui->end->value(),
                ui->interval->value(),
                10
                );

    ((MainWindow*) parent())->getControl()->measureSample( m );
}
