/*--------------------------------------------------------------------------*/
/*                           Compilation Control                            */
/*--------------------------------------------------------------------------*/
#ifndef _LUASCRIPT_H
#define _LUASCRIPT_H

/*--------------------------------------------------------------------------*/
/*                            Defined Constants                             */
/*--------------------------------------------------------------------------*/
typedef enum luaScriptStateTag {
    LSS_WAITFRAME,
    LSS_WAITTIME,
    LSS_RUNNING,
    LSS_NOTLOADED,
    LSS_DONE
} LUASCRIPTSTATE;

/*--------------------------------------------------------------------------*/
/*                              Data Structures                             */
/*--------------------------------------------------------------------------*/
class cpl_LuaManager;
typedef struct lua_State lua_State;

class cpl_LuaScript {
public: // ---------------------------------------
    cpl_LuaScript(cpl_LuaManager* mgr);
    ~cpl_LuaScript(void);

    void CreateThread(void);    
    void RunFile(char* fileName);
    void CallFn(char* fnName);
    void CallFn(char* fnName, int  iParam);
    void CallFn(char* fnName, int* iParam);
    void CallFn(char* fnName, const char *& sParam);
    void AbortWait(void);

    int  RunString(char* commandString);

    cpl_LuaScript* Update(float elapsedSec);
public: //------------------------------------------
    cpl_LuaManager* manager; // cpl_LuaManager object that created this script
    cpl_LuaScript* next;
    LUASCRIPTSTATE state;   // are we waiting, not loaded yet, etc.
    float waitTimestamp;    // time to wake up
    float time; // current time   
    int waitFrame;  // number of frames to wait
private:    // ---------------------------------------
    lua_State*  threadState;
    char lastErrorString[256];
    void ResumeScript(float param);
    void FormatError(void);
    void OutputError(char* strType);
};

#endif // _LUASCRIPT_H
