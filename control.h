#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QSerialPort>
#include <QSettings>
#include "parallelportdriver.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    ~Control();
    QString measurePoint();

signals:
    
public slots:
    void stop();
    void lift();
    void lower();
    void zeroing();

 private:
    QSerialPort * portti;
    QSettings * settings;
    PPort * pPortti;
};

#endif // CONTROL_H
