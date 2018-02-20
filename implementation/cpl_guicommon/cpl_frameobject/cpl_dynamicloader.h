#ifndef CPL_DYNAMICLOADER_H
#define CPL_DYNAMICLOADER_H

// They are different on several different OS's
#if defined(__hpux)
# include <dl.h> // Needed for special dynamic loading on hp
  typedef shl_t cpl_LibHandle;
#elif defined(_WIN32)
  typedef void* cpl_LibHandle;
#else
  typedef void* cpl_LibHandle;
#endif

class cpl_DynamicLoader : public cpl_Object {
    
public:
    /** create instance. */
    static cpl_DynamicLoader* New();

    /** load a dynamic library into the current process. */
    static cpl_LibHandle OpenLibrary(const char*);
    
    /** attempt to detach a dynamic library from the process. */
    static int CloseLibrary(cpl_LibHandle);

    /** find the address of the symbol in the given library */
    static void* GetSymbolAddress(cpl_LibHandle, const char*);

    /** return the library prefix for the given architecture */
    static const char* LibPrefix();

    /** return the library extension for the given architecture */
    static const char* LibExtension();

    /** return the last error produced from a calls made on this class. */
    static const char* LastError();
  
protected:
    // constructor.
    cpl_DynamicLoader();

    //destructor.
    virtual ~cpl_DynamicLoader();    
};

#endif //CPL_DYNAMICLOADER_H

