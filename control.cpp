/**
  * @file control.cpp
  * @brief Measurement control
  * All functions needed to control the measurement devices
  */
#include "control.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #define pPortWrite(chr) _outp(0x378,chr)
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif


/**
 * @brief Control::Control
 * @param parent
 */
Control::Control(QObject *parent) :
    QObject(parent)
{
}
/**
 * @brief Control::lift
 */
void Control::lift()
{
    pPortWrite('0');
}
/**
 * @brief Control::lower
 */
void Control::lower()
{

}

void Control::zeroing()
{
    portti->write("Z");
}

QString Control::measurePoint()
{
    char dataStorage[32];
    portti->write("M"); // send measurement order
    portti->read( dataStorage, 32 ); // receive value
    return QString( dataStorage );
}
