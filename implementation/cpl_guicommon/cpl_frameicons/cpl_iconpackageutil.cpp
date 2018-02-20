#include "cpl_frameiconincludes.h"

///// static variable and function /////

//------------------------------------------------------------------------
const char * makeIconUniqueName(const char * iconId, const char * solScheme) {
    //@@preconditions
    assert(iconId);
    assert(solScheme);
    //@@end preconditions

    static std::string iconIdString;
    iconIdString.clear();

    iconIdString  = solScheme;
    iconIdString += "_";
    iconIdString += iconId;

    return iconIdString.c_str();
}

//------------------------------------------------------------------------
int incrId(int & id)
{
   id++;
   return id;
}
