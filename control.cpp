/**
  * @file control.cpp
  * @brief Measurement control
  * All functions needed to control the measurement devices
  */
#include "control.h"
#include <QThread>
#include <QDebug>



/**
 * @brief Control::Control
 * @param parent
 */
Control::Control(QObject *parent) :
    QObject(parent)
{
    settings = new QSettings("Stemlux Systems", "Geologos");
    pPortti = new PPort(this); // parallel port
    settings->beginGroup("communication");
    portti = new QSerialPort( settings->value("portName").toString(), this );

    portti->setBaudRate(QSerialPort::Baud1200);
    portti->setDataBits(QSerialPort::Data7);
    portti->setParity(QSerialPort::NoParity);
    portti->setStopBits(QSerialPort::TwoStop);

    settings->endGroup();
}

Control::~Control()
{
    delete portti;
    delete settings;
    delete pPortti;
}
/**
 * @brief Fast lifting
 */
void Control::lift()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&pmutex);

    // load settings:
    settings->beginGroup("delays");
    int delay = settings->value("delay1").toInt();
    settings->endGroup();
    for( int i = 0; i < 25; i++)
    {
        qDebug() << pPortti->write( 16 );
        QThread::msleep( delay );
        pPortti->write( 64 );
        QThread::msleep( delay );
        pPortti->write( 32 );
        QThread::msleep( delay );
        pPortti->write( 128 );
        QThread::msleep( delay );
        pPortti->write( 0 );
    }
    pPortti->write( 0 );
    qDebug() << "lifted";
}
/**
 * @brief Control::lower
 */
void Control::lower()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&pmutex);

    // load settings:
    settings->beginGroup("delays");
    int delay = settings->value("delay1").toInt();
    int delay3 = settings->value("delay3").toInt();
    settings->endGroup();
    // first lower fast
    for( int i = 0; i < 10; i++)
    {
        pPortti->write( 16 );
        QThread::msleep( delay );
        pPortti->write( 64 );
        QThread::msleep( delay );
        pPortti->write( 32 );
        QThread::msleep( delay );
        pPortti->write( 128 );
        QThread::msleep( delay );
        pPortti->write( 0 );
    }
    // then lower slow
    for( int i = 0; i < 15; i++)
    {
        pPortti->write( 16 );
        QThread::msleep( delay3 );
        pPortti->write( 64 );
        QThread::msleep( delay3 );
        pPortti->write( 32 );
        QThread::msleep( delay3 );
        pPortti->write( 128 );
        QThread::msleep( delay3 );
        pPortti->write( 0 );
    }
    pPortti->write( 0 );
    qDebug() << "lowered";
}

void Control::zeroing()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&smutex);

    if( !portti->isOpen() );
        //portti->open(OpenMode);
    portti->write("Z");
}

void Control::stepForward()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&pmutex);

    // load settings:
    settings->beginGroup("delays");
    int delay = settings->value("delay2").toInt();
    settings->endGroup();

    for (int i=0; i < 67; i++)
    {
        //out 888,1
        pPortti->write( 1 );
        //gosub viive2
        QThread::msleep( delay );
        //out 888,4
        pPortti->write( 4 );
        //gosub viive2
        QThread::msleep( delay );
        //out 888,2
        pPortti->write( 2 );
        //gosub viive2
        QThread::msleep( delay );
        pPortti->write( 8 );
        //gosub viive2
        QThread::msleep( delay );
    }
    pPortti->write( 0 );
}

void Control::stepBack()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&pmutex);

    // load settings:
    settings->beginGroup("delays");
    int delay = settings->value("delay2").toInt();
    settings->endGroup();

    for (int i=0; i < 67; i++)
    {
        //out 888,1
        pPortti->write( 2 );
        //gosub viive2
        QThread::msleep( delay );
        //out 888,4
        pPortti->write( 4 );
        //gosub viive2
        QThread::msleep( delay );
        //out 888,2
        pPortti->write( 1 );
        //gosub viive2
        QThread::msleep( delay );
        pPortti->write( 8 );
        //gosub viive2
        QThread::msleep( delay );
    }
    pPortti->write( 0 );
}

QString Control::measurePoint()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&smutex);

    char dataStorage[32];
    portti->open(QIODevice::ReadWrite);
    qDebug() << portti->write("M"); // send measurement order
    QThread::msleep(1000);
    qDebug() << portti->read( dataStorage, 32 ); // receive value
    qDebug() << dataStorage;
    return QString( dataStorage );
}

void Control::stop()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker0(&pmutex);
    QMutexLocker locker1(&smutex);

    pPortti->write(0);
    portti->close();
    qDebug() << "measurement stopped!";
}
