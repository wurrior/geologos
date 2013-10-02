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
    if( !portti->isOpen() )
        portti->open(QIODevice::ReadWrite);
    qDebug() << portti->write("M"); // send measurement order
    QThread::msleep(1000);
    qDebug() << portti->read( dataStorage, 32 ); // receive value
    qDebug() << dataStorage;
    return QString( dataStorage );
}


bool Control::measureSample(Measurement *m)
{
    // clear stop flag
    clearStop();
    qDebug() << "measuring sample...";
    // only one measurement can be done at a time:
    if( !mmutex.tryLock() ) return false;
    //UUSI:
    //cls
    //screen 9:REM grafiikkatila
    //kux=10:kuy=300:REM alkupiste k„yr„lle
    //gx1=kux:gy1=kuy
    //kk=alku
    //'kerroin=1
    //lippu1=0:REM onko eka data, jolla skaalataan k„yr„„
    //lippu2=0
    //gosub xakseli: REM piirr„ x-akseli
    //for b=kk to vika
    for(int i = m->getBegin(); i < m->getEnd(); i++)
    {
        //  check for user initiated stop:
        if( stopped ) {
            mmutex.unlock();
            return false;
        }

        //		gosub laske
        lower();
        //      delay (1);
        //	print #1,"M": input #1,s$
        //		GOSUB TALTEEN
        m->addResult( measurePoint() );
        //	sound 333,1.5
        //		gosub nosta
        lift();
        //	delay (1.5);
        //	datay=0
        //	print #1,"M":input #1,A$
        //        datay=val(s$)
        //        datay=datay-val(a$)
        //	'if lippu1=0 then a=a: if datay<20 then kerroin=8 else kerroin=1:lippu1=1
        //		GOSUB TALTEENILMA
        m->addAirValue( measurePoint() );
        //        datay=datay*kerroin
        //        if datay>300 then datay=datay-300
        //        gx2=gx1+hyppy:gy2=kuy-datay
        //	if gx2>600 then line(10,kuy)-(gx2,kuy),7:gx2=10:gx1=10:kuy=kuy :cls:gosub xakseli: rem uusi alku
        //	if lippu2=1 then a=a: line (gx1,gy1)-(gx2,gy2),15
        //        circle(gx2,gy2),2
        //	gx1=gx2:gy1=gy2
        //        kux=kux+2

        //  check for user initiated stop:
        if( stopped ) {
            mmutex.unlock();
            return false;
        }


        //	sound 500,1.0
        //        if hyppy=2 then qkierros=1
        //        if hyppy=4 then qkierros=2
        //        if hyppy=6 then qkierros=3
        //        if hyppy=8 then qkierros=4
        //        if hyppy=10 then qkierros=5
        //        	gosub monta
        for(int k = 0; k < m->getInterval()<<1; k++)
            stepBack();
        //        lippu2=1:rem viiva vasta tokalla kerralla
        //        if inkey$<>"" then screen 0:goto menu
    }
    //	next b
    //        screen 0
    //GOTO MENU
    mmutex.unlock();
    stop(); // stop
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
    emit measurementStopped( stopped );

    // ensure that only one thread is accessing the port:
    QMutexLocker locker0(&pmutex);
    QMutexLocker locker1(&smutex);

    pPortti->write(0);
    qDebug() << "measurement stopped!";
}
