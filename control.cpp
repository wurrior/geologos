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
    QObject(parent),
    stopped(true),
    high(true)
{
    settings = new QSettings("Stemlux Systems", "Geologos");
    pPortti = new PPort(this); // parallel port
    settings->beginGroup("communication");
    //open port and set it up:
    portti = new QSerialPort( settings->value("portName").toString(), this );
    portti->setBaudRate(QSerialPort::Baud1200);
    portti->setDataBits(QSerialPort::Data7);
    portti->setParity(QSerialPort::NoParity);
    portti->setStopBits(QSerialPort::TwoStop);

    settings->endGroup();
}

Control::~Control()
{
    portti->close();
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
    pPortti->write( 0 );

    qDebug() << "lifted";
    high = true;
    emit isHigh( high );
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
    high = false;
    emit isHigh( high );
}

void Control::zeroing()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&smutex);

    if( !portti->isOpen() )
        portti->open(QIODevice::ReadWrite);
    portti->write("Z\n");
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
        QThread::usleep( delay );
        //out 888,4
        pPortti->write( 4 );
        //gosub viive2
        QThread::usleep( delay );
        //out 888,2
        pPortti->write( 2 );
        //gosub viive2
        QThread::usleep( delay );
        pPortti->write( 8 );
        //gosub viive2
        QThread::usleep( delay );
    }
    pPortti->write( 0 );
}

void Control::forwards()
{
    for(int i = 0; i < 1000; i++)
    {
        stepBack();
    }
}

void Control::stepBack()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&pmutex);

    // load settings:
    settings->beginGroup("delays");
    int delay = settings->value("delay2").toInt();
    if(delay == 0) delay++;
    settings->endGroup();

    for (int i=0; i < 67; i++)
    {
        //out 888,1
        pPortti->write( 2 );
        //gosub viive2
        QThread::usleep( delay );
        //out 888,4
        pPortti->write( 4 );
        //gosub viive2
        QThread::usleep( delay );
        //out 888,2
        pPortti->write( 1 );
        //gosub viive2
        QThread::usleep( delay );
        pPortti->write( 8 );
        //gosub viive2
        QThread::usleep( delay );
    }
    pPortti->write( 0 );
    qDebug() << "moved one step back 2mm";
}

void Control::backwards()
{
    for(int i = 0; i < 1000; i++)
    {
        stepBack();
    }
}

QString Control::measurePoint()
{
    // ensure that only one thread is accessing the port:
    QMutexLocker locker(&smutex);

    // String to store value:
    QString temp;

    if( !portti->isOpen() )
    {
        portti->open(QIODevice::ReadWrite);
    }

    QThread::sleep(1);

    // send and receive:
    if( portti->write("M\n") != -1 ) do{
        portti->waitForReadyRead(600000);
        temp.append( portti->readAll() );
    } while( temp.isEmpty() );

    emit dataReceived();
    return temp;
}


bool Control::measureSample(Measurement *m)
{
    // clear stop flag
    clearStop();

    int jump = m->getInterval();
    qDebug() << "interval: " << jump;
    qDebug() << "measuring sample...";

    // only one measurement can be done at a time:
    if( !mmutex.tryLock() ) return false;

    for(int i = m->getBegin(); i < m->getEnd(); i+=jump)
    {
        // lower head:
        if( !stopped ) lower();

        // read value from sample:
        if( !stopped ) m->addResult( measurePoint() );

        // lift head:
        if( !stopped ) lift();

        // read value from air:
        if( !stopped ) m->addAirValue( measurePoint() );

        // move to next position:
        if( !stopped )
            for(int k = 0; k < (jump>>1); k++)
                stepBack();

    }

    mmutex.unlock();

    // check for user initiated stop:
    if( stopped ) {
        if(!high) lift();
        return false;
    } else stop(); // stop

    return true;
}

void Control::clearStop()
{
    stopped = false;
    emit measurementStopped( stopped );
}

void Control::stop()
{
    // stop measurement:
    stopped = true;

    // ensure that only one thread is accessing the port:
    QMutexLocker locker0(&pmutex);
    QMutexLocker locker1(&smutex);

    pPortti->write(0);
    emit measurementStopped( stopped );
    qDebug() << "measurement stopped!";
}
