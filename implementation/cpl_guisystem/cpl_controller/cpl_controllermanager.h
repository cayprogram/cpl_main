#ifndef CPL_CONTROLLERMANAGER_H
#define CPL_CONTROLLERMANAGER_H

class cpl_GUIEngine;
class cpl_LuaProxy;
class cpl_ScriptProxy;
class cpl_SessionProxy;
class cpl_PluginTreeProxy;
class cpl_FileIOController;
class cpl_MultiFileIOController;
class cpl_IconProxy;
class cpl_ImageProxy;
class cpl_ControllerManagerLuaWrapper;

//-----------------------------------------------------------------
class cpl_ControllerManager : public cpl_ControllerSet {

public:
    /** create Instance */
    static cpl_ControllerManager * New();

public:    
    /** Initialize */
    virtual void DoInitialization(int argc, char * * argv);

    /** cleanup */
    virtual void DoCleanup();

public:
    //api 
    /** load components */
    virtual void LoadServices();

    /** enter event loop */
    virtual void EnterEventLoop();

    /** Set break flag. */
    virtual void SetBreakFlagOn();

    /** Do Command Id */
    virtual int  DoCommand(char* scriptcomand, void* userData, char* cmdData);

public:
    /** get plugin tree*/
    virtual void* GetPluginTree();

    /** get file io */
    virtual void* GetFileIOHandler();

    /** get file io */
    virtual void* GetMultiFileIOHandler();

    /** get lua script */
    virtual void* GetLuaScript();

    /** get session proxy */
    virtual void* GetSessionProxy();

    /** get icon proxy */
    virtual void* GetIconProxy();

    /** get image proxy */
    virtual void* GetImageProxy();

public:
    /** get ui engine */
    virtual cpl_GUIEngine* GetGUIEngine(); 
    
public:
    /** register script lib */
    virtual int  RegisterScriptLib() { return 0; }

    /** Register interfaces */
    virtual int  RegisterInterfaces(char* path, char* name, void* data);

public:
    /** run session */
    virtual void RunSessionFile(const char* fname) {}

    /** run lua script */
    virtual void RunLuaScriptFile(const char* fname);

    /** run lua script */
    virtual void RunLuaScriptCommand(const char* buffer);

public:
    /** set enabled */
    virtual int SetEnabled(int state);

    /** get enabled */
    virtual int GetEnabled();

public:
    //constructor.
    cpl_ControllerManager();

    //destructor
    virtual ~cpl_ControllerManager();

protected:
    //initialized flag.
    int IsInitialized;

    //enabled;
    int IsEnabled;

    //main gui engine
    cpl_GUIEngine* mainGUIEngine;

    //pObject Creator.
    cpl_Creator* ObjectCreator;

    //controller lists.
    cpl_LuaProxy              * pControllerLuaScript;
    cpl_ScriptProxy           * pControllerScript;
    cpl_SessionProxy          * pControllerSession;
    cpl_PluginTreeProxy       * pControllerPluginTree;
    cpl_FileIOController      * pControllerFileIO;
    cpl_MultiFileIOController * pControllerMultiFileIO;
    cpl_IconProxy             * pControllerIcon;
    cpl_ImageProxy            * pControllerImage;

    //script handler
    cpl_ControllerManagerLuaWrapper* luaWrapper;
};

#endif //CPL_CONTROLLERMANAGER_H
