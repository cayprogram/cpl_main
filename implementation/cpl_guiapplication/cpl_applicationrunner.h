#ifndef CPL_APPLICATIONRUNNER_H
#define CPL_APPLICATIONRUNNER_H

#include <simpleopt.h>

//-----------------------------------------------------------------------------
//options macro.
//-----------------------------------------------------------------------------
#define OPT_ID_SESSION    1
#define OPT_ID_LUA        2
#define OPT_ID_LUA_BUFFER 3

//-----------------------------------------------------------------------------
class cpl_Application;
class cpl_ApplicationRunner {

public:
    /** initialize */
    int Initialize(int argc, char * * argv);

    /** running. */
    int Running(); 
    
    /** clean up */
    int Cleanup(); 

public:
    /** set lua filename */
    void SetLuaFileName(const char* script);

    /** set lua script buffer */
    void SetLuaScriptBuffer(const char* script);

    /** set session file */
    void SetSessionFileName(const char* fname);

public:
    // Constructor
    cpl_ApplicationRunner(cpl_Application * appInst);

    // Destructor
    virtual ~cpl_ApplicationRunner();

public:
    enum{ MAX_OPTS = 10 };

    //process command arguments.
    int ProcessCommandLineArg(int argc, char * * argv);

    //enter GUI mode 
    int DoRunningLoop();
    int DoCommandLineAction();

    //member variables.
    int Options[MAX_OPTS];
    char* sessionFileName;
    char* luaFileName;
    char* luaCommandBuffer;    
    cpl_Application * theApp;
    CSimpleOpt* cmdOptions;
};

#endif //CPL_APPLICATIONRUNNER_H
