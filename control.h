#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QSerialPort>
#include <QSettings>
#include <QMutex>
#include "parallelportdriver.h"
#include "measurement.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    ~Control();
    QString measurePoint();
    bool measureSample( Measurement * m );

    void backwards();
    void forwards();
signals:
    void measurementStopped(bool stopped);
    void isHigh(bool high);
    void dataReceived();
    
public slots:
    void clearStop();
    void stop();
    void lift();
    void lower();
    void zeroing();
    void stepForward();
    void stepBack();

 private:
    QSerialPort * portti;
    QSettings * settings;
    PPort * pPortti;
    QMutex smutex;
    QMutex pmutex;
    QMutex mmutex;
    bool stopped;
    bool high;
};

#endif // CONTROL_H
