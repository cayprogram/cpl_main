#ifndef CPL_CONTROLLERMANAGERLUAWRAPPER_H
#define CPL_CONTROLLERMANAGERLUAWRAPPER_H

class cpl_ControllerManager;
class cpl_ControllerManagerLuaWrapper {
public: 
    // operations to export lua script
    int SetOutputWindowOnOff(lua_State* L);
    int ExecCommand(lua_State* L);
public:
    static char const className[];
    static Lunar<cpl_ControllerManagerLuaWrapper>::RegType methods[];

public:
    /** do initialization */
    void DoInitialization(cpl_ControllerManager* pOwner);

    /** do clean up */
    void DoCleanup();

public:
    /** default constructor */
    cpl_ControllerManagerLuaWrapper(lua_State* L);

    /** destructor */
    virtual ~cpl_ControllerManagerLuaWrapper();

protected:
    //protected variables.
    cpl_ControllerManager* pControlManager;
};

#endif //CPL_CONTROLLERMANAGERLUAWRAPPER_H