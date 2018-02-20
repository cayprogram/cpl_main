#include "cpl_controllerapplicationincludes.h"

//local includes.
#include <cpl_guiengine/cpl_applicationguiengineimpincludes.h>
// #include <ls_dialog.h>
#include <ls_script.h>

//-----------------------------------------------------------------------------
// class cpl_ApplicationControllerManager
//-----------------------------------------------------------------------------
//
cpl_ApplicationControllerManager * cpl_ApplicationControllerManager::New() {
    return (cpl_ApplicationControllerManager*)cpl_ControllerObjectFactory::Instance()->CreateControlManager();
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::DoInitialization(int argc, char * * argv) {
    //@@preconditions
    assert(this->IsInitialized == 0);
    //@@end preconditions

    //load services required.
    this->LoadServices();    

    //init script.
    this->LuaScript("init()");

    //load GUI object factory.
    this->LoadGUIObjectFactory();

    //call parent initialization.
    this->cpl_ControllerManager::DoInitialization(argc, argv); 

    //load components.
    this->LoadComponents();

    //update status.
    this->IsInitialized = 1;
    this->IsEnabled = 1;

    //register services.
    pl_ExecuteFunction("_AUTOSTART");
    pl_ExecuteFunction("_INITSYSTEM");

    //main script, if necessary.
    this->LuaScript("main()");
    
    //message.
    this->mainGUIEngine->GetOutputStatusInfoHandler()->StatusTextA("Ready");
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::DoCleanup() {
    //deinit script.
    this->LuaScript("deinit()");

    //execute auto end.
    pl_ExecuteFunction("_AUTOEND");
    pl_ShutDown();

    //shutdown.
//     DLGShutDown();

    //call superclass
    this->cpl_ControllerManager::DoCleanup();
}

//-----------------------------------------------------------------------------
int cpl_ApplicationControllerManager::LoadGUIObjectFactory() {
    //initialize GUI object factory.
    cpl_GUIObjectFactory::SetFactory(new cpl_ApplicationGUIObjectFactory());
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_ApplicationControllerManager::LoadComponents() {

    //initialize dialog manager.
//     DLGInitialize();

    //create link.
//     void* pdata = NULL;
//     DLGGetDialogManager(&pdata);
//     assert(pdata != NULL);

    //register services.
    this->RegisterInterfaces("/Workbench/Interfaces/Services/RuntimeContext"        , "RuntimeContext"         , this->mainGUIEngine->GetRuntimeContextProxy());
//     this->RegisterInterfaces("/Workbench/Interfaces/Services/WindowStylerCollection", "WindowStylerCollection" , pdata);
    this->RegisterInterfaces("/Workbench/Interfaces/Services/FileIO"                , "FileIO"                 , this->GetFileIOHandler());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/MultiFileIO"           , "MultiFileIO"            , this->GetMultiFileIOHandler());    
    this->RegisterInterfaces("/Workbench/Interfaces/Services/PanelFunction"         , "PanelFunction"          , this->mainGUIEngine->GetTaskPanelProxy());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/OutputStatus"          , "OutputStatus"           , this->mainGUIEngine->GetOutputStatusInfoHandler());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/Output"                , "Output"                 , this->mainGUIEngine->GetOutputMessage());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/GraphicWindow"         , "GraphicWindow"          , this->mainGUIEngine->GetGraphicWindowInfoHandler());    
    this->RegisterInterfaces("/Workbench/Interfaces/Services/SessionFile"           , "SessionFile"            , this->GetSessionProxy());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/SystemWindow"          , "SystemWindow"           , this->mainGUIEngine->GetSystemWindowRawHandler());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/SessionWindow"         , "SessionWindow"          , this->mainGUIEngine->GetSessionWindowRawHandler());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/Layout"                , "Layout"                 , this->mainGUIEngine->GetLayoutProxy());
    this->RegisterInterfaces("/Workbench/Interfaces/Services/Icon"                  , "Icon         "          , this->mainGUIEngine->GetIconProxy());

    //init control module.
    pl_Initialize();

    //register services. 
    pl_ServiceRegisterManager(this->GetPluginTree());
    pl_ServiceBind();

    //start default process.
    pl_StartDefaultProcess();

    return 0;
}

//-----------------------------------------------------------------------------
int cpl_ApplicationControllerManager::RegisterScriptLib() {

    ILuaScriptProxy* luaScript = (ILuaScriptProxy*)this->GetLuaScript();
    assert(luaScript != NULL);

    //extern lib list.
    extern void LuaOpenScriptLib(lua_State*);
    luaScript->RegisterLib(LuaOpenScriptLib);

    extern const char* prog;
    luaScript->RunString(prog);
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::LuaScript(const char* command) {
    //@@preconditions
    assert(command != NULL);
    //@@end preconditions

    this->RunLuaScriptCommand(command);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::RunSessionFile(const char* fname) {
    //@@preconditions
    assert(fname != NULL);
    //@@end preconditions

    pl_FuncServerSetInputAsSTRING(PS_PARAM_0, (char*)fname);
    pl_ExecuteFunction("_OPENSESSIONDIRECT");
}

//-----------------------------------------------------------------------------
// EVENT HANDLER
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int cpl_ApplicationControllerManager::DoCommand(char* scriptcomand, void* userData, char* cmdData) {
    //@@preconditions
    assert(scriptcomand != NULL);
    //@@end preconditions

    if (this->GetEnabled() == 0) {
        return 0;
    }

    //event handle.
    if (strcmp(scriptcomand, "OGLPANEL_CLICKED") == 0) {
        this->OnGraphicWindowClicked(userData);
        return 1;
    }
    if (strcmp(scriptcomand, "OGLPANEL_DOUBLECLICKED") == 0) {
        this->OnGraphicWindowDoubleClicked(userData);
        return 1;
    }
    if (strcmp(scriptcomand, "CONTEXTMENU") == 0) {
        this->OnGraphicWindowContextMenu(userData);
        return 1;
    }
    if (strcmp(scriptcomand, "THREAD") == 0) {
        this->OnThreadTest();
        return 1;
    }
    if (scriptcomand[0] == '>') {
        return pl_ExecuteFunction(&scriptcomand[1]);
        return 1;
    }
    if (scriptcomand[0] == '@') { //lua command.
        ((ILuaScriptProxy*)this->GetLuaScript())->CallFn(&scriptcomand[1]);
        return 1;
    }
    if (scriptcomand[0] == '*') { //lua command.
        int retVal = -999;
        ((ILuaScriptProxy*)this->GetLuaScript())->CallFn(&scriptcomand[1], retVal);
        return retVal;
    }
    if (scriptcomand[0] == '#') { //lua buffer.
        ((ILuaScriptProxy*)this->GetLuaScript())->RunString(&scriptcomand[1]);
        return 1;
    }
    //execute command.
    return pl_ExecuteFunction(scriptcomand);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::OnGraphicWindowClicked(void* data) {
    //@@preconditions
    assert(data != NULL);
    assert(this->mainGUIEngine != NULL);
    //@@end preconditions

    int* wid = (int*)(data);
    assert(wid != NULL);

    if (this->mainGUIEngine->GetLayoutProxy()->GetExchangeMode() == 0) {
        if (wid[0]>= 0) {
            pl_FuncServerSetInputAsINT(PS_PARAM_0, wid[0]);
            pl_ExecuteFunction("_SETCURRENTVIEW");             
            pl_ExecuteFunction("_SWITCHMODELINFO");  //will refresh gui components 
        }
    }
    else {
        IGraphicWindowInfo* graphicInfo = this->mainGUIEngine->GetGraphicWindowInfoHandler();
        assert(graphicInfo != NULL);

        int idx_source = graphicInfo->GetActiveGraphicWindowId(); 
        int idx_target = wid[0];
        this->mainGUIEngine->GetLayoutProxy()->DoExchange(idx_source, idx_target);
        this->mainGUIEngine->GetLayoutProxy()->SetExchangeMode(0);
    }
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::OnGraphicWindowContextMenu(void* data) {
    //@@preconditions
    assert(data != NULL);
    assert(this->mainGUIEngine != NULL);
    //@@end preconditions

    int* wid = (int*)(data);
    assert(wid != NULL);

    if (wid[0]>= 0) {
        pl_FuncServerSetInputAsINT(PS_PARAM_0, wid[0]);
        pl_ExecuteFunction("_SETCURRENTVIEW");             
        pl_ExecuteFunction("_SWITCHMODELINFO");  //will refresh gui components 
    }
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::OnGraphicWindowDoubleClicked(void* data) {
    //@@preconditions
    assert(data != NULL);
    //@@end preconditions

    pl_ExecuteFunction("_SWITCHLAYOUTMODE");
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::OnThreadTest() {
    //@@preconditions
    assert(this->mainGUIEngine != NULL);
    //@@end preconditions

    IThreadFunc* pThread = this->mainGUIEngine->GetThreadFunc();
    assert(pThread != NULL);

    pThread->Exec(this, cpl_ApplicationControllerManager::OnThreadTestCallback);
}

//-----------------------------------------------------------------------------
void cpl_ApplicationControllerManager::OnThreadTestCallback(void* callData, void* clientData) {
    //@@preconditions
    assert(callData != NULL);
    assert(clientData != NULL);
    //@@end preconditions

    IThreadFunc* pThread = (IThreadFunc*)callData;
    assert(pThread != NULL);

    for (int k = 0; k < 100; k++) {
        for (int j = 0; j < 10; j++) {
            for (int i = 0; i < 5000000; i++) {
                float value = (float)sqrt((double)(i*10));
                float ppppp = sqrt(value*value);
                value = value+ppppp;
            }
        }
        //update gui thread.
        pThread->UpdateGUIState(k*10);
    }
}

//-----------------------------------------------------------------------------
cpl_ApplicationControllerManager::~cpl_ApplicationControllerManager() {
}
