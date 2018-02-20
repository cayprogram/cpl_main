#include "cpl_outputframeincludes.h"
#include "encodingconversion.h"

//-----------------------------------------------------------------------------
cpl_OutputProxyImp::cpl_OutputProxyImp() {
    this->posInsert = 0;
    this->posLookup = 0;
    this->outputAllowed = 1;
    this->stringBuffer = new cpl_OutputBuffer;
    this->stringBuffer->Allocate(MAX_STRING_NUM);    
}

//-----------------------------------------------------------------------------
cpl_OutputProxyImp::~cpl_OutputProxyImp() {
    if (this->stringBuffer != NULL) {
        delete this->stringBuffer;
    }
}

//-----------------------------------------------------------------------------
void cpl_OutputProxyImp::EnableOutput() {
    this->outputAllowed = 1;
}

//-----------------------------------------------------------------------------
void cpl_OutputProxyImp::DisableOutput() {
    this->outputAllowed = 0;
}

//-----------------------------------------------------------------------------
void cpl_OutputProxyImp::OutputText(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions

    char * utf8_string = win32_mbcs_to_utf8(text); 
    assert(utf8_string);

    //we should scroll output buffer.
    if (posInsert == MAX_STRING_NUM) { 
        this->stringBuffer->ScrollUp(1);        
        this->stringBuffer->SetItemText(this->posInsert-1, utf8_string);
    }
    else {
        this->stringBuffer->SetItemText(this->posInsert++, utf8_string);
    }
    delete[] utf8_string;
}

//-----------------------------------------------------------------------------
void cpl_OutputProxyImp::SynchorizeWithDisplay() {
    //@@preconditions
    assert(this->stringBuffer != NULL);
    assert(this->posLookup >= 0);
    //@@end preconditions
}

//-----------------------------------------------------------------------------
void cpl_OutputProxyImp::OutputTextCallback(void* data1, void* data2) {
    //@@preconditions
    assert(data1 != NULL);
    assert(data2 != NULL);
    //@@end preconditions

    cpl_OutputProxyImp* THIS_IS = (cpl_OutputProxyImp*)data2;
    assert(THIS_IS != NULL);

    THIS_IS->OutputText((char*)data1);
}
