#ifndef PARALLELPORTDRIVER_H
#define PARALLELPORTDRIVER_H

#include <QObject>

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>

/* Definitions in the build of inpout32.dll are:            */
/*   short _stdcall Inp32(short PortAddress);               */
/*   void _stdcall Out32(short PortAddress, short data);    */

/* prototype (function typedef) for DLL function Inp32: */
typedef short _stdcall (*inpfuncPtr)(short portaddr);
typedef void _stdcall (*oupfuncPtr)(short portaddr, short datum);

#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif


class PPort : public QObject
{
    Q_OBJECT
public:
    explicit PPort(QObject *parent = 0);
    bool write(const char data);
signals:
    
public slots:
    
private:
    #if defined(_WIN32) || defined(_WIN64)
    HINSTANCE hLib;
    inpfuncPtr inp32;
    oupfuncPtr oup32;
    #endif
};

#endif // PARALLELPORTDRIVER_H
