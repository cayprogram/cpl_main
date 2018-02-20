#ifndef CPL_OUTPUTBUFFER_H
#define CPL_OUTPUTBUFFER_H

class cpl_OutputBuffer {

public:    
    /** set/get text ith item */
    void  SetItemText(int i, const char* text);
    char* GetItemText(int i);
       
    /** allocate. */
    virtual int Allocate(int sz);

    /** remove all action */
    virtual int RemoveAllItems();

    /** get number Item */
    virtual int GetNumberOfItem();
   
    /** scroll up */
    virtual int ScrollUp(int scrollNum);

public:    
    //constructor
    cpl_OutputBuffer();
        
    //destructor
    virtual ~cpl_OutputBuffer();

protected:             
    //inner structure
    struct fbString_s{
        char* text;
    };

    //protected variables
    fbString_s* Array;
    int Size;
};

//-----------------------------------------------------------------------------
inline void cpl_OutputBuffer::SetItemText(int i, const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    assert(i >= 0);
    assert(i < this->Size);
    assert(this->Array != NULL);
    //@@end preconditions

    if (this->Array[i].text != NULL) {
        delete[] this->Array[i].text;
        this->Array[i].text = NULL;
    }
    size_t len = strlen(text);
    this->Array[i].text = new char[len + 1];
    strcpy(this->Array[i].text, text);
    this->Array[i].text[len] = '\0';
}

//-----------------------------------------------------------------------------
inline char* cpl_OutputBuffer::GetItemText(int i) {
    //@@preconditions
    assert(i >= 0);
    assert(i < this->Size);
    assert(this->Array != NULL);
    //@@end preconditions

    return this->Array[i].text;
}

//-----------------------------------------------------------------------------
inline int cpl_OutputBuffer::GetNumberOfItem() {
    return this->Size;
}

#endif //CPL_OUTPUTBUFFER_H
