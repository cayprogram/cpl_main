#ifndef _LUASCRIPTUTILITY_H
#define _LUASCRIPTUTILITY_H

/*--------------------------------------------------------------------------*/
/*                              Data Structures                             */
/*--------------------------------------------------------------------------*/

typedef struct lua_State lua_State;

/*--------------------------------------------------------------------------*/
/*                            Public Prototypes                             */    
/*--------------------------------------------------------------------------*/
class cpl_LuaScriptUtilty {
    
public: //------------------------------------------
    static int GetInteger                 (lua_State *L, int index, int           &val);
    static int GetDouble                  (lua_State *L, int index, double        &val); 
    static int GetFloat                   (lua_State *L, int index, float         &val);
    static int GetString                  (lua_State *L, int index, const char   *&val);
    static int GetArrayInteger            (lua_State *L, int index, int          *&array);
    static int GetArrayDouble             (lua_State *L, int index, double       *&array); 
    static int GetArrayFloat              (lua_State *L, int index, float        *&array);
    static int GetArrayUnsignedInteger    (lua_State *L, int index, unsigned int *&array);
    static int GetArrayUnsignedChar       (lua_State *L, int index, unsigned char*&array);
    static int GetArrayString             (lua_State *L, int index, const char  **&array);
    static int GetVOID                    (lua_State *L, int index, void         *&val);
    
    static int SetRetInteger              (lua_State *L, int           val);
    static int SetRetDouble               (lua_State *L, double        val); 
    static int SetRetFloat                (lua_State *L, float         val);
    static int SetRetString               (lua_State *L, const char    *val);
    static int SetRetVOID                 (lua_State *L, void          *val);
    static int SetRetArrayInteger         (lua_State *L, int           *array, int size);
    static int SetRetArrayDouble          (lua_State *L, double        *array, int size); 
    static int SetRetArrayFloat           (lua_State *L, float         *array, int size);
    static int SetRetArrayUnsignedInteger (lua_State *L, unsigned int  *array, int size);
    static int SetRetArrayUnsignedChar    (lua_State *L, unsigned char *array, int size);
    static int SetRetArrayString          (lua_State *L, const char   **array, int size);

public://------------------------------------------
    static int FreeArray(void* array);
    
public: // ---------------------------------------
    cpl_LuaScriptUtilty();
    ~cpl_LuaScriptUtilty(void);
};

#define LuaD_getInteger              cpl_LuaScriptUtilty::GetInteger                
#define LuaD_getDouble               cpl_LuaScriptUtilty::GetDouble                 
#define LuaD_getFloat                cpl_LuaScriptUtilty::GetFloat                   
#define LuaD_getString               cpl_LuaScriptUtilty::GetString                 
#define LuaD_getVoid                 cpl_LuaScriptUtilty::GetVOID                 
#define LuaD_getArrayInteger         cpl_LuaScriptUtilty::GetArrayInteger           
#define LuaD_getArrayDouble          cpl_LuaScriptUtilty::GetArrayDouble            
#define LuaD_getArrayFloat           cpl_LuaScriptUtilty::GetArrayFloat              
#define LuaD_getArrayUnsignedChar    cpl_LuaScriptUtilty::GetArrayUnsignedChar      
#define LuaD_getArrayUnsignedInteger cpl_LuaScriptUtilty::GetArrayUnsignedInteger
#define LuaD_getArrayString          cpl_LuaScriptUtilty::GetArrayString

#define LuaD_retInteger              cpl_LuaScriptUtilty::SetRetInteger             
#define LuaD_retDouble               cpl_LuaScriptUtilty::SetRetDouble              
#define LuaD_retFloat                cpl_LuaScriptUtilty::SetRetFloat               
#define LuaD_retString               cpl_LuaScriptUtilty::SetRetString  
#define LuaD_retVoid                 cpl_LuaScriptUtilty::SetRetVOID                            
#define LuaD_retArrayInteger         cpl_LuaScriptUtilty::SetRetArrayInteger         
#define LuaD_retArrayDouble          cpl_LuaScriptUtilty::SetRetArrayDouble          
#define LuaD_retArrayFloat           cpl_LuaScriptUtilty::SetRetArrayFloat          
#define LuaD_retArrayUnsignedInteger cpl_LuaScriptUtilty::SetRetArrayUnsignedInteger 
#define LuaD_retArrayUnsignedChar    cpl_LuaScriptUtilty::SetRetArrayUnsignedChar    
#define LuaD_retArrayString          cpl_LuaScriptUtilty::SetRetArrayString   

#define LuaD_freeArray               cpl_LuaScriptUtilty::FreeArray

#endif // _LUASCRIPTUTILITY_H
