#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <mainwindow.h>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    settings = new QSettings("Stemlux Systems", "Geologos");
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
    delete settings;
}

void SettingsWindow::showAndRefresh()
{
    // com ports:
    ui->comboBox_com_port->clear();
    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts()) {
        ui->comboBox_com_port->addItem( info.portName() );
    }
    settings->beginGroup("communication");
    ui->comboBox_com_port->setCurrentText( settings->value("portName").toString() );
    settings->endGroup();

    // allert user if no comport is present:
    if( !QSerialPortInfo::availablePorts().size() )
    {
        QMessageBox msgBox;
        msgBox.setText("COM port not found!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }

    // delays:
    settings->beginGroup("delays");
    ui->spinBox_delay_1->setValue( settings->value("delay1",100).toInt() );
    ui->spinBox_delay_2->setValue( settings->value("delay2",500).toInt() );
    ui->spinBox_delay_3->setValue( settings->value("delay3",1000).toInt() );
    settings->endGroup();

    this->show();
}

void SettingsWindow::on_buttonBox_accepted()
{
    settings->beginGroup("communication");
    settings->setValue("portName", ui->comboBox_com_port->currentText() );
    settings->setValue("portNumber", ui->lineEdit->text() );
    qDebug() << settings->value("portName").toString();
    settings->endGroup();

    settings->beginGroup("delays");
    settings->setValue("delay1",ui->spinBox_delay_1->value());
    settings->setValue("delay2",ui->spinBox_delay_2->value());
    settings->setValue("delay3",ui->spinBox_delay_3->value());
    settings->endGroup();

}
void SettingsWindow::on_checkBox_clicked(bool checked)
{
    ((MainWindow*)parent())->toggleAdvancedControls(checked);
}
