#include "cpl_outputframeincludes.h"

//-----------------------------------------------------------------------------
// class cpl_OutputBuffer
//-----------------------------------------------------------------------------
//
cpl_OutputBuffer::cpl_OutputBuffer() {
    this->Array = NULL;
    this->Size  = 0;
}

//-----------------------------------------------------------------------------
cpl_OutputBuffer::~cpl_OutputBuffer() {
    if (this->Array != NULL) {
        for (int i = 0; i < this->Size; i++) {
            if (this->Array[i].text != NULL) {
                delete[] this->Array[i].text;
                this->Array[i].text = NULL;
            }
        }
        delete[] this->Array;
        this->Array = NULL;
    }
}

//-----------------------------------------------------------------------------
int cpl_OutputBuffer::Allocate(int sz) {
    //@@preconditions
    assert(sz > 0);
    //@@end preconditions

    if (sz > this->Size || this->Array == NULL) {
        if (this->Array != NULL) {
            for (int i = 0; i < this->Size; i++) {
                if (this->Array[i].text != NULL) {
                    delete[] this->Array[i].text;
                    this->Array[i].text = NULL;
                }
            }
            delete[] this->Array;
        }
        this->Size = (sz > 0 ? sz : 1);
        this->Array = new fbString_s[this->Size];
        if (this->Array == NULL) {
            return 0;
        }
        for (int i = 0; i < this->Size; i++) {
             this->Array[i].text    = NULL;
        }
    }

    return 1;
}

//-----------------------------------------------------------------------------    
int cpl_OutputBuffer::RemoveAllItems(){
    for (int i = 0; i < this->Size; i++) {
        if (this->Array[i].text != NULL) {
            delete[] this->Array[i].text;
            this->Array[i].text = NULL;
        }
    }
    //it mean you have to allocate again.
    delete[] this->Array;
    this->Array = NULL;
    this->Size = 0;

    return 1;
}

//-----------------------------------------------------------------------------
int cpl_OutputBuffer::ScrollUp(int scrollNum) {
    //preconditions
    assert(scrollNum >= 0);
    assert(scrollNum < this->Size);
    //@@end preconditions

    for (int i = 0; i < this->Size; i++) {
        if (i < scrollNum) {
            if (this->Array[i].text != NULL) {
                delete[] this->Array[i].text;
                this->Array[i].text = NULL;
            }
            continue;
        }
        this->Array[i-scrollNum].text = this->Array[i].text;
        this->Array[i].text = NULL;
    }
    return 1;
}
