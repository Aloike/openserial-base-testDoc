#include "CInterfaceSerialSingleton.h"


/* ########################################################################## */
/* ########################################################################## */

CInterfaceSerialSingleton*  CInterfaceSerialSingleton::s_m_instance = 0;

/* ########################################################################## */
/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief Constructor of the CInterfaceSerialSingleton class.
 */
CInterfaceSerialSingleton::CInterfaceSerialSingleton()
    :   CInterfaceSerial( 0 )
{

}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Destructor of the CInterfaceSerialSingleton class.
 */
CInterfaceSerialSingleton::~CInterfaceSerialSingleton()
{
    if( this->isOpen() )
    {
        this->close();
    }
}

/* ########################################################################## */
/* #### STATIC METHODS ###################################################### */
/* ########################################################################## */
/**
 *  @brief  This static method returns a pointer to the unique instance of the
 *          singleton.
 *
 *  @return A CInterfaceSerialSingleton pointer to the unique instance.
 */
CInterfaceSerialSingleton*  CInterfaceSerialSingleton::instance()
{
    if( s_m_instance == 0 ) {
        s_m_instance    = new CInterfaceSerialSingleton();
    }

    return s_m_instance;
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  This static method destroys the unique instance of the singleton.
 */
void    CInterfaceSerialSingleton::freeInstance()
{
    if( s_m_instance != 0 )
    {
        delete s_m_instance;
        s_m_instance    = 0;
    }
}

/* ########################################################################## */
/* ########################################################################## */
