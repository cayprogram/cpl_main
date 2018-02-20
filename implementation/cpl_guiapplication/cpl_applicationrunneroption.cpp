#include <cpl_guisystemincludes.h>

//local includes.
#include "cpl_applicationrunner.h"

//-----------------------------------------------------------------------------
CSimpleOpt::SOption g_rgFlags[] = {
    { SO_O_EXACT,       "--exact",          SO_NONE },
    { SO_O_NOSLASH,     "--noslash",        SO_NONE },
    { SO_O_SHORTARG,    "--shortarg",       SO_NONE },
    { SO_O_CLUMP,       "--clump",          SO_NONE },
    { SO_O_NOERR,       "--noerr",          SO_NONE },
    { SO_O_PEDANTIC,    "--pedantic",       SO_NONE },
    { SO_O_ICASE,       "--icase",          SO_NONE },
    { SO_O_ICASE_SHORT, "--icase-short",    SO_NONE },
    { SO_O_ICASE_LONG,  "--icase-long",     SO_NONE },
    { SO_O_ICASE_WORD,  "--icase-word",     SO_NONE },
    SO_END_OF_OPTIONS
};

//-----------------------------------------------------------------------------
enum { 
    OPT_HELP = 0,
    OPT_SESSION = 100, 
    OPT_LUA, 
    OPT_CONSOLE,
    OPT_LUACOMMAND,   
};

CSimpleOpt::SOption g_rgOptions[] = {
    { OPT_HELP,        "-?",           SO_NONE    },
    { OPT_HELP,        "-h",           SO_NONE    },
    { OPT_HELP,        "-help",        SO_NONE    },
    { OPT_HELP,        "--help",       SO_NONE    },
    {  1,              "-",            SO_NONE    },
    {  2,              "-d",           SO_NONE    },
    {  3,              "-e",           SO_NONE    },
    {  4,              "-f",           SO_NONE    },
    {  5,              "-g",           SO_NONE    },
    {  6,              "-flag",        SO_NONE    },
    {  7,              "--flag",       SO_NONE    },
    {  8,              "-s",           SO_REQ_SEP },
    {  9,              "-c",           SO_REQ_CMB },
    { 10,              "-o",           SO_OPT     },
    { OPT_SESSION,     "-session",     SO_REQ_SEP },
    { OPT_LUA    ,     "-lua",         SO_REQ_SEP },
    { OPT_LUACOMMAND,  "-luacommand",  SO_REQ_SEP },
    SO_END_OF_OPTIONS
};

//-----------------------------------------------------------------------------
static const char * GetLastErrorText(int a_nError)  {
    switch (a_nError) {
        case SO_SUCCESS:            return "Success";
        case SO_OPT_INVALID:        return "Unrecognized option";
        case SO_OPT_MULTIPLE:       return "Option matched multiple strings";
        case SO_ARG_INVALID:        return "Option does not accept argument";
        case SO_ARG_INVALID_TYPE:   return "Invalid argument format";
        case SO_ARG_MISSING:        return "Required argument is missing";
        case SO_ARG_INVALID_DATA:   return "Invalid argument data";
        default:                    return "Unknown error";
    }
}

//-----------------------------------------------------------------------------
static void ShowUsage() {
    printf("Usage: app.exe [OPTIONS] [FILES]\n");
    printf("\n");
    printf("-session FILE                               Run session file.\n");
    printf("-lua FILE                                   Run lua script file.\n");
    printf("-luacommand buffer                          Run lua command .\n");
    printf("-?  -h  -help  --help                       Output this help.\n");
    printf("\n");
}

//-----------------------------------------------------------------------------
int cpl_ApplicationRunner::ProcessCommandLineArg(int argc, char * * argv) {
    //@@preconditions
    assert(this->cmdOptions != NULL);
    //@@end preconditions

    int nFlags = SO_O_USEALL;
    this->cmdOptions->Init(argc, argv, g_rgFlags, SO_O_NOERR|SO_O_EXACT);
    while (this->cmdOptions->Next()) {
        nFlags |= this->cmdOptions->OptionId();
    }    

    this->cmdOptions->Init(this->cmdOptions->FileCount(), this->cmdOptions->Files(), g_rgOptions, nFlags);
    while (this->cmdOptions->Next()) {
        if (this->cmdOptions->LastError() != SO_SUCCESS) {
            printf("%s: '%s' (use --help to get command line help)\n", GetLastErrorText(this->cmdOptions->LastError()), this->cmdOptions->OptionText());
            continue;
        }        
        switch (this->cmdOptions->OptionId()) {
            case OPT_HELP:
                ShowUsage();
                return 0;
            case OPT_SESSION:  
                this->Options[OPT_ID_SESSION] = 1;
                this->SetSessionFileName(this->cmdOptions->OptionArg());
                break;
            case OPT_LUA: 
                this->Options[OPT_ID_LUA] = 1;
                this->SetLuaFileName(this->cmdOptions->OptionArg());                    
                break;
            case OPT_LUACOMMAND: 
                this->Options[OPT_ID_LUA_BUFFER] = 1;
                this->SetLuaScriptBuffer(this->cmdOptions->OptionArg());
                break;
            default: 
                break;
        }
    }
    return 1;
}   
