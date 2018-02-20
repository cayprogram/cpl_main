#ifndef CPL_OUTPUTPROXYIMP_H
#define CPL_OUTPUTPROXYIMP_H

class cpl_OutputProxyImp {

public:
    /** output text */
    virtual void OutputText(const char* text);

    /** synchronize with display */
    virtual void SynchorizeWithDisplay();

    /** Output Enabled*/
    virtual void EnableOutput();

    /** Output Disable */
    virtual void DisableOutput();

    /** output callback */
    static void OutputTextCallback(void* data1, void* data2);

public:
    //constructor.
    cpl_OutputProxyImp();

    //destructor
    virtual ~cpl_OutputProxyImp();

protected:
    friend class cpl_HistoryInfoOutputWindow;

    enum { MAX_STRING_NUM = 1000};
    
    //output buffer.
    cpl_OutputBuffer* stringBuffer;  
    int posInsert;
    int posLookup;
    int outputAllowed;
};

#endif //CPL_OUTPUTPROXYIMP_H
