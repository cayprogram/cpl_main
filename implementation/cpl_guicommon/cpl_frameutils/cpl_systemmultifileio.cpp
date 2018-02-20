#include "cpl_frameutilsincludes.h"

//-----------------------------------------------------------------------------
cpl_SystemMultiFileIO * cpl_SystemMultiFileIO::instance = NULL;

//-----------------------------------------------------------------------------
cpl_SystemMultiFileIO * cpl_SystemMultiFileIO::Instance() {
    return cpl_SystemMultiFileIO::instance;
}

//-----------------------------------------------------------------------------
void cpl_SystemMultiFileIO::Delete() {
    if (cpl_SystemMultiFileIO::instance) {
        delete cpl_SystemMultiFileIO::instance;
        cpl_SystemMultiFileIO::instance = NULL;
    }
}

//-----------------------------------------------------------------------------
void cpl_SystemMultiFileIO::SetInstance(cpl_SystemMultiFileIO* factory) {
    //@@preconditions
    assert(factory != NULL);
    //@@end preconditions

    cpl_SystemMultiFileIO::instance = factory;
}

//-----------------------------------------------------------------------------
cpl_SystemMultiFileIO::~cpl_SystemMultiFileIO() {
}
