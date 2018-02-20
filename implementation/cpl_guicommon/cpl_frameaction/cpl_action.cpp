#include "cpl_actionframeincludes.h"

//-----------------------------------------------------------------------------
//global static data.
//-----------------------------------------------------------------------------
static cpl_Action::_fbAction_s ActionData = { NULL, NULL, NULL, NULL, 1, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL};

//-----------------------------------------------------------------------------
// class cpl_Action
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
void cpl_Action::SetText(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions

    if (this->actionData.text != NULL) {
        delete[] this->actionData.text;
        this->actionData.text = NULL;
    }
    size_t len = strlen(text);
    this->actionData.text = new char[len+1];
    assert(this->actionData.text != NULL);

    strcpy(this->actionData.text, text);
    this->actionData.text[len] ='\0';
}

//-----------------------------------------------------------------------------
const char* cpl_Action::GetText() {
    //@@postconditions
    assert(this->actionData.text != NULL);
    //@@end postconditions

    return this->actionData.text;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetShortCut(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions

    if (this->actionData.shortcut != NULL) {
        delete[] this->actionData.shortcut;
        this->actionData.shortcut = NULL;
    }
    size_t len = strlen(text);
    this->actionData.shortcut = new char[len+1];
    assert(this->actionData.shortcut != NULL);

    strcpy(this->actionData.shortcut, text);
    this->actionData.shortcut[len] ='\0';
}

//-----------------------------------------------------------------------------
const char* cpl_Action::GetShortCut() {
    //@@postconditions
    //@@end postconditions

    return this->actionData.shortcut;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetStringId(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions

    if (this->actionData.textid != NULL) {
        delete[] this->actionData.textid;
        this->actionData.textid = NULL;
    }
    size_t len = strlen(text);
    this->actionData.textid = new char[len+1];
    assert(this->actionData.textid != NULL);

    strcpy(this->actionData.textid, text);
    this->actionData.textid[len] ='\0';
}

//-----------------------------------------------------------------------------
const char* cpl_Action::GetStringId() {
    //@@postconditions
    assert(this->actionData.textid != NULL);
    //@@end postconditions

    return this->actionData.textid;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetEnable(int enable) {
    //@@preconditions
    assert(enable == 1 || enable == 0);
    //@@end preconditions

    this->actionData.enable = enable;
}

//-----------------------------------------------------------------------------
int  cpl_Action::GetEnable() {
    //@@preconditions
    assert(this->actionData.enable == 1 || this->actionData.enable == 0);
    //@@end preconditions

    return this->actionData.enable;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetType(int type) {
    this->actionData.type = type;
}

//-----------------------------------------------------------------------------
int cpl_Action::GetType() {
    return this->actionData.type;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetChecked(int checked) {
    this->actionData.checked = checked;
}

//-----------------------------------------------------------------------------
int cpl_Action::GetChecked() {
    return this->actionData.checked;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetDivider(int divider) {
    this->actionData.divider = divider;
}

//-----------------------------------------------------------------------------
int cpl_Action::GetDivider() {
    return this->actionData.divider;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetPixmap(const char * name) {
    if (this->actionData.pixmap != NULL) {
        delete[] this->actionData.pixmap;
        this->actionData.pixmap = NULL;
    }
    size_t len = strlen(name);
    this->actionData.pixmap = new char[len+1];
    assert(this->actionData.pixmap != NULL);

    strcpy(this->actionData.pixmap, name);
    this->actionData.pixmap[len] ='\0';
}

//-----------------------------------------------------------------------------
const char * cpl_Action::GetPixmap() {
    return this->actionData.pixmap;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetDomain(const char * name) {
    if (this->actionData.domain != NULL) {
        delete[] this->actionData.domain;
        this->actionData.domain = NULL;
    }
    size_t len = strlen(name);
    this->actionData.domain = new char[len+1];
    assert(this->actionData.domain != NULL);

    strcpy(this->actionData.domain, name);
    this->actionData.domain[len] ='\0';
}

//-----------------------------------------------------------------------------
const char * cpl_Action::GetDomain() {
    return this->actionData.domain;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetTooltip(char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions

    if (this->actionData.tooltip != NULL) {
        delete[] this->actionData.tooltip;
        this->actionData.tooltip = NULL;
    }
    size_t len = strlen(text);
    this->actionData.tooltip = new char[len+1];
    assert(this->actionData.tooltip != NULL);

    strcpy(this->actionData.tooltip, text);
    this->actionData.tooltip[len] ='\0';
}

//-----------------------------------------------------------------------------
char* cpl_Action::GetTooltip() {
    return this->actionData.tooltip;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetUserData(void* UserData) {
    this->actionData.userdata = UserData;
}

//-----------------------------------------------------------------------------
void* cpl_Action::GetUserData() {
    return this->actionData.userdata;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetCommandId(int cmdId) {
    this->actionData.cmdid = cmdId;
}

//-----------------------------------------------------------------------------
int  cpl_Action::GetCommandId() {
    return this->actionData.cmdid;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetCommandData(const char* text) {
    //@@preconditions
    assert(text != NULL);
    assert(strlen(text) > 0);
    //@@end preconditions

    if (this->actionData.cmddata != NULL) {
        delete[] this->actionData.cmddata;
        this->actionData.cmddata = NULL;
    }
    size_t len = strlen(text);
    this->actionData.cmddata = new char[len+1];
    assert(this->actionData.cmddata != NULL);

    strcpy(this->actionData.cmddata, text);
    this->actionData.cmddata[len] ='\0';
}

//-----------------------------------------------------------------------------
const char* cpl_Action::GetCommandData() {
    //@@postconditions
    assert(this->actionData.cmddata != NULL);
    //@@end postconditions

    return this->actionData.cmddata;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetComposite(cpl_ActionComposite* parent) {
    //@@preconditions
    assert(parent != NULL);
    //@@end preconditions
    
    this->actionData.parent = parent;
}
   
//-----------------------------------------------------------------------------
cpl_ActionComposite* cpl_Action::GetComposite() {
    return this->actionData.parent;
}

//-----------------------------------------------------------------------------
int cpl_Action::IsComposite() {
    return 0;
}

//-----------------------------------------------------------------------------
void cpl_Action::SetIconId(const char * iconId) {
    if (this->actionData.iconid != NULL) {
        delete[] this->actionData.iconid;
        this->actionData.iconid = NULL;
    }
    if (!iconId) return;

    size_t len = strlen(iconId);
    this->actionData.iconid = new char[len+1];
    assert(this->actionData.iconid != NULL);

    strcpy(this->actionData.iconid, iconId);
    this->actionData.iconid[len] ='\0';
}

//-----------------------------------------------------------------------------
const char * cpl_Action::GetIconId() {
    return this->actionData.iconid;
}

//-----------------------------------------------------------------------------
int cpl_Action::GetNumberOfSubActions() {
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_Action::GetNumberOfNestSubActions() {
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_Action::Execute() {
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_Action::Execute(int argc, char** argv) {
    return 0;
}

//-----------------------------------------------------------------------------
cpl_Action::cpl_Action() {
    this->actionData  = ActionData;
}

//-----------------------------------------------------------------------------
cpl_Action::cpl_Action(cpl_ActionComposite* pAction) {
    this->actionData        = ActionData;
    this->actionData.parent = pAction;
}

//-----------------------------------------------------------------------------
cpl_Action::cpl_Action(const char* text, const char* shortcut, int enable, int type, int cmdid, void * userdata, cpl_ActionComposite* parent) {
    this->actionData.enable   = enable;
    this->actionData.type     = type;
    this->actionData.cmdid    = cmdid;
    this->actionData.divider  = 0;
    this->actionData.checked  = 0;
    this->actionData.userdata = userdata;
    this->actionData.parent   = parent;
    this->actionData.text     = NULL;
    this->actionData.tooltip  = NULL;
    this->actionData.textid   = NULL;
    this->actionData.shortcut = NULL;
    this->actionData.textidchecked = NULL;
    this->actionData.pixmap   = NULL;
    this->actionData.domain   = NULL;
    this->actionData.shortcut = NULL;
    this->actionData.iconid   = NULL;
    this->actionData.cmddata  = NULL;

    if (text != NULL) {
        this->SetText(text);
    }    
    if (shortcut != NULL) {
        this->SetShortCut(shortcut);
    }   
}

//-----------------------------------------------------------------------------
cpl_Action::cpl_Action(const char* text, const char* stringid, const char* shortcut, int enable, int type, int cmdid, int checked, char* tooltip, const char * pixmap_name, const char* domain, void * userdata, cpl_ActionComposite* parent) {
    this->actionData.enable   = enable;
    this->actionData.type     = type;
    this->actionData.cmdid    = cmdid;
    this->actionData.checked  = checked;   
    this->actionData.divider  = 0;
    this->actionData.userdata = userdata;
    this->actionData.parent   = parent;
    this->actionData.text     = NULL;
    this->actionData.tooltip  = NULL;
    this->actionData.textid   = NULL;
    this->actionData.shortcut = NULL;
    this->actionData.textidchecked = NULL;
    this->actionData.pixmap   = NULL;
    this->actionData.shortcut = NULL;
    this->actionData.domain   = NULL;
    this->actionData.iconid   = NULL;
    this->actionData.cmddata  = NULL;

    if (text != NULL) {
        this->SetText(text);
    }    
    if (tooltip != NULL) {
        this->SetTooltip(tooltip);
    }
    if (stringid != NULL) {
        this->SetStringId(stringid);
    }
    if (pixmap_name != NULL) {
        this->SetPixmap(pixmap_name);
    }
    if (domain != NULL) {
        this->SetDomain(domain);
    }
    if (shortcut != NULL) {
        this->SetShortCut(shortcut);
    }  
}

//-----------------------------------------------------------------------------
cpl_Action::~cpl_Action() {
    if (this->actionData.text != NULL) {
        delete[] this->actionData.text;
        this->actionData.text = NULL;
    }
    if (this->actionData.textid != NULL) {
        delete[] this->actionData.textid;
        this->actionData.textid = NULL;
    }
   if (this->actionData.shortcut != NULL) {
        delete[] this->actionData.shortcut;
        this->actionData.shortcut = NULL;
    }
    if (this->actionData.pixmap != NULL) {
        delete[] this->actionData.pixmap;
        this->actionData.pixmap = NULL;
    }
    if (this->actionData.tooltip != NULL) {
        delete[] this->actionData.tooltip;
        this->actionData.tooltip = NULL;
    }
    if (this->actionData.domain != NULL) {
        delete[] this->actionData.domain;
        this->actionData.domain = NULL;
    }
    if (this->actionData.iconid != NULL) {
        delete[] this->actionData.iconid;
        this->actionData.iconid = NULL;
    }
    if (this->actionData.cmddata != NULL) {
        delete[] this->actionData.cmddata;
        this->actionData.cmddata = NULL;
    }
}
