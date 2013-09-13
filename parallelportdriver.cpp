#include "parallelportdriver.h"

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
}
bool PPort::write(quint16 chr)
{
#if defined(_WIN32) || defined(_WIN64)
    bool success;
    // open printer port for writing:
    HANDLE pPortti = CreateFile( L"LPT1",
                               (GENERIC_READ | GENERIC_WRITE),
                               0,
                               0,
                               OPEN_EXISTING,
                               0,
                               0);
    // write one byte:
    success = WriteFile(pPortti,&chr,1,NULL,NULL);
    // check for errors and return:
    return ( success & ( pPortti != INVALID_HANDLE_VALUE ));
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif
}
