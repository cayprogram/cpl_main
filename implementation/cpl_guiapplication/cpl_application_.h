#ifndef CPL_APPLICATION__H
#define CPL_APPLICATION__H

class cpl_Application_ : public cpl_Application {

public:
    /** Initialize. */
    virtual void Initialize(int argc, char * * argv);

    /** Cleanup. */
    virtual void Cleanup();
    
public:
    /** constructor */
    cpl_Application_();

    /** destructor */
    virtual ~cpl_Application_() {}
};

#endif //CPL_APPLICATION__H
