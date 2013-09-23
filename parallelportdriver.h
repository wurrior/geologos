#ifndef PARALLELPORTDRIVER_H
#define PARALLELPORTDRIVER_H

#include <QObject>

#include <windows.h>

/* Definitions in the build of inpout32.dll are:            */
/*   short _stdcall Inp32(short PortAddress);               */
/*   void _stdcall Out32(short PortAddress, short data);    */

/* prototype (function typedef) for DLL function Inp32: */
typedef short _stdcall (*inpfuncPtr)(short portaddr);
typedef void _stdcall (*oupfuncPtr)(short portaddr, short datum);

class PPort : public QObject
{
    Q_OBJECT
public:
    explicit PPort(QObject *parent = 0);
    bool write(const char data);
signals:
    
public slots:
    
private:
    HINSTANCE hLib;
    inpfuncPtr inp32;
    oupfuncPtr oup32;
};

#endif // PARALLELPORTDRIVER_H
