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

signals:
    
public slots:
    void stop();
    void rise();
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
};

#endif // CONTROL_H
