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
    pPortti = new PPort(this);
}

Control::~Control()
{
    delete settings;
    delete pPortti;
}
/**
 * @brief Fast lifting
 */
void Control::lift()
{
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
}
/**
 * @brief Control::lower
 */
void Control::lower()
{
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
}

void Control::zeroing()
{
    portti->write("Z");
}

QString Control::measurePoint()
{
    char dataStorage[32];
    //portti->open();
    portti->write("M"); // send measurement order
    portti->read( dataStorage, 32 ); // receive value
    return QString( dataStorage );
}

void Control::stop()
{
    pPortti->write(0);
    //portti->close();
    qDebug() << "measurement stopped!";
}
