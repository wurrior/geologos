#include "parallelportdriver.h"
#include <QDebug>
#include <QFile>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif

PPort::PPort(QObject *parent) :
    QObject(parent)
{
    //=======================================================================
    qDebug() << "Loading!";
    /* Load the library */
    hLib = LoadLibraryA("inpout32.dll");

    if (hLib == NULL) {
        qDebug() << "Lib not loaded";
        return;
    }

    /* get the address of the function */

    inp32 = (inpfuncPtr) GetProcAddress(hLib, "Inp32");

    if (inp32 == NULL) {
        qDebug() << "input failed";
         return;
    }

    oup32 = (oupfuncPtr) GetProcAddress(hLib, "Out32");

    if (oup32 == NULL) {
        qDebug() << "output failed";
         return;
    }
    //=======================================================================

}
bool PPort::write(const char data)
{

#if defined(_WIN32) || defined(_WIN64)
    (oup32)(888, data);
    return true;//( filu.putChar( data ) );
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif
}
