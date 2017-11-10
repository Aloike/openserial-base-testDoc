#ifndef CINTERFACESERIALSINGLETON_H
#define CINTERFACESERIALSINGLETON_H

#include "CInterfaceSerial.h"


class CInterfaceSerialSingleton : public CInterfaceSerial
{
    Q_OBJECT



/* -----------------------------------------------------------------------------
 *  Methods
 * -------------------------------------------------------------------------- */
public:

    static  CInterfaceSerialSingleton*  instance(void);
    static  void                        freeInstance(void);



protected:
private:

    CInterfaceSerialSingleton();
    ~CInterfaceSerialSingleton();



/* -----------------------------------------------------------------------------
 *  Slots
 * -------------------------------------------------------------------------- */
public slots:
protected slots:
private slots:



/* -----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------- */
public:
protected:
private:

    static  CInterfaceSerialSingleton*  s_m_instance;



};

#endif /*< CINTERFACESERIALSINGLETON_H */
