#include "parallelportdriver.h"
#include <QDebug>
#include <QFile>

PPort::PPort(QObject *parent) :
    QObject(parent)
{
    #if defined(_WIN32) || defined(_WIN64)
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
#elif __linux
    qDebug() << "parallel port not in use";
#endif
}

bool PPort::write(const char data)
{
#if defined(_WIN32) || defined(_WIN64)
    (oup32)(888, data);
    //qDebug() << "parallel data written";
    return true;
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif
}
