#include "newmeasurement.h"
#include "ui_newmeasurement.h"

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
