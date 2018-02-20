#ifndef CPL_ACTION_H
#define CPL_ACTION_H

/** cpl_Action class simulate a menu item . */
class cpl_CompositeAction;
class cpl_Action {
public:
    //[properties]
    /** set/get command id */
    void SetCommandId(int cmdId);
    int  GetCommandId();

    /** set/get command data */
    void SetCommandData(const char * text);
    const char * GetCommandData();

    /** set/get text. */
    void SetText(const char* text);
    const char* GetText();

    /** set/get string id. */
    void SetStringId(const char* text);
    const char* GetStringId();

    /** set/get shortcut. */
    void SetShortCut(const char* shortcut);
    const char* GetShortCut();

    /** enable/disable */
    void SetEnable(int enable);
    int  GetEnable();

    /** set/get type. */
    void SetType(int type);
    int  GetType();

    /** set/get tooltip. */
    void SetTooltip(char* tooltip);
    char* GetTooltip();

    /** set/get pixmap. */
    void SetPixmap(const char * name);
    const char * GetPixmap();

    /** set/get Checked. */
    void SetChecked(int checked);
    int  GetChecked();

    /** set/get divide. */
    void SetDivider(int divider);
    int  GetDivider();

    /** set/get domain data */
    void SetDomain(const char * name);
    const char * GetDomain();

    /** set/get user data. */
    void  SetUserData(void* userdata);
    void* GetUserData();

    /** set/get icon string id. */
    void SetIconId(const char * iconId);
    const char * GetIconId();

public:
    /** get number of sub action. */
    virtual int GetNumberOfSubActions();

    /** get number of sub action (nested). */
    virtual int GetNumberOfNestSubActions();
    
    /** is composite or not. */
    virtual int IsComposite();

    /** execute  */
    virtual int Execute();

    /** execute  */
    virtual int Execute(int argc, char** argv);

public:
    /** set composite action */
    virtual void SetComposite(cpl_ActionComposite* pcAction);
    
    /** get composite action */
    virtual cpl_ActionComposite* GetComposite();

public:
    //inner structure.
    struct _fbAction_s {
        char* text;
        char* textid;
        char* textidchecked;
        char* shortcut;
        int   enable;
        int   type;
        int   cmdid;
        int   checked;
        int   divider;
        void* userdata;
        char* tooltip;        
        char* pixmap;
        char* domain;
        char* iconid;   ///icon resource loaded from xml(=NULL -- invalid; !=NULL -- valid)
        char* cmddata;
        cpl_ActionComposite* parent;
    };

    //constructor. 1
    cpl_Action();
    
    //constructor. 2
    cpl_Action(cpl_ActionComposite* parent);

    //constructor. 3
    cpl_Action(const char* text, const char* shortcut, int enable, int type, int cmdid, void * userdata, cpl_ActionComposite* parent);

    //constructor. 4
    cpl_Action(const char* text, const char* stringid, const char* shortcut, int enable, int type, int cmdid, int checked, char* tooltip, const char * pixmap_name, const char* domain, void * userdata, cpl_ActionComposite* parent);

    //destructor.
    virtual ~cpl_Action();

    //protected variables   
    _fbAction_s actionData;
};

#endif //CPL_ACTION_H
