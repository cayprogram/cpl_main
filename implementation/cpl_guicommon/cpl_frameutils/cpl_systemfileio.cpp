#include "cpl_frameutilsincludes.h"

//-----------------------------------------------------------------------------
cpl_SystemFileIO * cpl_SystemFileIO::instance = NULL;

//-----------------------------------------------------------------------------
cpl_SystemFileIO * cpl_SystemFileIO::Instance() {
    return cpl_SystemFileIO::instance;
}

//-----------------------------------------------------------------------------
void cpl_SystemFileIO::Delete() {
    if (cpl_SystemFileIO::instance) {
        delete cpl_SystemFileIO::instance;
        cpl_SystemFileIO::instance = NULL;
    }
}

//-----------------------------------------------------------------------------
void cpl_SystemFileIO::SetInstance(cpl_SystemFileIO* factory) {
    //@@preconditions
    assert(factory != NULL);
    //@@end preconditions

    cpl_SystemFileIO::instance = factory;
}

//-----------------------------------------------------------------------------
cpl_SystemFileIO::~cpl_SystemFileIO() {
}
