#include "newmeasurement.h"
#include "ui_newmeasurement.h"
#include "mainwindow.h"
#include "control.h"

NewMeasurement::NewMeasurement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMeasurement)
{
    ui->setupUi(this);
}

NewMeasurement::~NewMeasurement()
{
    delete ui;
}

void NewMeasurement::on_buttonBox_accepted()
{
    ((MainWindow*) parent())->setMeasurement(
    // create new Measurement
     new Measurement(
                ui->begin->value(),
                ui->end->value(),
                ui->interval->value(),
                10
                )
                );
}

void NewMeasurement::on_interval_valueChanged(int arg1)
{
    if( arg1 < 2 ) ui->interval->setValue(2);
    else ui->interval->setValue((arg1>>1)<<1);
}
