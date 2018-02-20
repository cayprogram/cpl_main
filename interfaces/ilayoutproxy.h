#ifndef LAYOUTPROXYINTERFACE_H
#define LAYOUTPROXYINTERFACE_H

class ILayoutProxy {
public:
    /** get layout active comp */
    virtual int  GetLayoutActiveComp() = 0;

    /** set layout active comp */
    virtual int  SetLayoutActiveComp(int compid) = 0;

    /** set layout type */
    virtual int  SetLayoutType(int type) = 0;

    /** get layout type */
    virtual int  GetLayoutType() = 0; 

    /** set layout mode */
    virtual int  SetLayoutMode(int mode) = 0;

    /** get layout mode */
    virtual int  GetLayoutMode() = 0;

    /** update layout */
    virtual void UpdateLayout() = 0;

    /** set exchange mode */
    virtual int SetExchangeMode(int mode) = 0;

    /** get exchange mode */
    virtual int GetExchangeMode() = 0;

    /** do exchange */
    virtual void DoExchange(int comp_src, int comp_target) = 0;
};

#endif //LAYOUTPROXYINTERFACE_H
