#include "cpl_frameobjectincludes.h"

#ifndef isWhite
#define isWhite(c) (c == ' '|| c == '\n' || c == '\r' || c == '\t')
#endif

//-----------------------------------------------------------------------------
static char *strnew(const char *val) {
    if ( val == NULL ) return(NULL);
    char *s = (char*)malloc(strlen(val)+1);
    strcpy(s, val);
    return(s);
}

//-----------------------------------------------------------------------------
// class cpl_String
//-----------------------------------------------------------------------------
//
cpl_String::cpl_String() {
    this->str = strnew("");
}

//-----------------------------------------------------------------------------
cpl_String::cpl_String( unsigned int len ) {
    if (len > 0) {
        this->str = (char*)malloc( len );
    }
    else {
        this->str = strnew("");
    }    
}

//-----------------------------------------------------------------------------
cpl_String::cpl_String( const char *s ) {
    this->str = strnew("");
   *this = s;
}

//-----------------------------------------------------------------------------
cpl_String::cpl_String( const cpl_String & s ) {
    this->str = strnew("");
   *this = s.str;
}

//-----------------------------------------------------------------------------
cpl_String::~cpl_String() {
    if (this->str != NULL) {
        free(this->str);
        this->str = NULL;
    }    
}

//-----------------------------------------------------------------------------
void cpl_String::copy(const char * s, unsigned int start, unsigned int len ) {
    if (s == 0) return;
    if (len == 0) return;
    if (start+len > strlen(s) ) return;
    if (this->str) free(this->str);
    this->str = (char*)malloc( len+1 );
    strncpy(this->str, s+start, len );
    this->str[len] = '\0';
}

//-----------------------------------------------------------------------------
int cpl_String::compare(const cpl_String &s) const {
    return strcmp(this->str, s.str );
}

//-----------------------------------------------------------------------------
int cpl_String::casecompare(const cpl_String &s) const {
    cpl_String s1(str), s2(s);
    s1.upcase();
    s2.upcase();
    return strcmp( s1.str, s2.str );
}

//-----------------------------------------------------------------------------
void cpl_String::upcase() {
    size_t l = strlen(this->str);
    for(size_t i = 0; i < l; i++ ) {
        str[i] = (char)toupper((int)str[i]);
    }    
}

//-----------------------------------------------------------------------------
void cpl_String::downcase() {
    size_t l = strlen(this->str);
    for(size_t i = 0; i < l; i++ ) {
        this->str[i] = (char)tolower((int)this->str[i]);
    }    
}

//-----------------------------------------------------------------------------
int cpl_String::find(char c) const {
    const char *i = strchr(str, c);
    if( !i ) {
        return -1;
    }    
    else {
        return i-str;
    }    
}

//-----------------------------------------------------------------------------
int cpl_String::find(char c, int pos) const {
    if (pos > this->size()) {
        return -1;
    }
    const char *i = strchr(&str[pos], c);
    if( !i ) {
        return -1;
    }    
    else {
        return i-str;
    }    
}

//-----------------------------------------------------------------------------
int cpl_String::rfind(char c) const {
    const char *i = strrchr(str, c);
    if ( !i ) {
        return -1;
    }    
    else {
        return i-str;
    }    
}

//-----------------------------------------------------------------------------
cpl_String cpl_String::substr(int pos, int len) const {
    if ((pos+len) <= 0 || (pos+len) > size()) {
        return cpl_String("");
    }    
    else {
        char *buf = (char*)malloc(len+1);
        strncpy( buf, str+pos, len );
        buf[len] = '\0';
        cpl_String s = buf;
        free( buf );
        return s;
    }
}

//-----------------------------------------------------------------------------
cpl_String& cpl_String::operator =(const char *s) { 
    char* tmp;
    if (s == 0) {
        tmp = strnew("");
    }    
    else {
        tmp = strnew(s);
    }    
    if (this->str != NULL) {
        free(this->str);
    }    
    this->str = tmp;
    return *this;
}

//-----------------------------------------------------------------------------
cpl_String& cpl_String::operator += (const char *s) {
    if (s == 0) {
        s = "";
    }    
    char *old = strnew(this->str);
    size_t lold = strlen(old), ls = strlen(s);
    free(this->str);
    this->str = (char*)malloc( lold + ls + 1 );
    memcpy(this->str, old, lold );
    memcpy(this->str+lold, s, ls );
    this->str[lold+ls] = '\0';
    free(old);
    return *this;
}

//-----------------------------------------------------------------------------
char* cpl_String::operator() () { 
    return str; 
}

//-----------------------------------------------------------------------------
const char* cpl_String::c_str() const { 
    return str; 
}

//-----------------------------------------------------------------------------
char& cpl_String::operator [](int i) { 
    return str[i]; 
}

//-----------------------------------------------------------------------------
char  cpl_String::operator [](int i) const { 
    return str[i]; 
}

//-----------------------------------------------------------------------------
void cpl_String::copy(const cpl_String& s) { 
    *this = s; 
}

//-----------------------------------------------------------------------------
void cpl_String::copy(const char *s) { 
    *this = s; 
}

//-----------------------------------------------------------------------------
void cpl_String::push_back(char c) { 
     char s[2] = { c, '\0' }; 
    *this += s; 
}

//-----------------------------------------------------------------------------
void cpl_String::copy(const cpl_String& s, unsigned int start, unsigned int len) { 
    copy( s.c_str(), start, len ); 
}

//-----------------------------------------------------------------------------
int cpl_String::size() const { 
    return (int)strlen(str); 
}

//-----------------------------------------------------------------------------
void cpl_String::trim() {
    int len = size();
    if (len == 0) {
        return;
    }
    int ibegin = 0;
    while (isWhite(str[ibegin])) {
        ibegin++;
    }
    int iend = len;
    while (isWhite(str[iend - 1])) {
        iend--;
    }
    cpl_String s = substr(ibegin, iend-ibegin);
    this->copy(s);
}

//-----------------------------------------------------------------------------
bool cpl_String::operator < (const cpl_String& s) const { 
    return (strcmp(str, s.str) < 0); 
}

//-----------------------------------------------------------------------------
bool cpl_String::operator > (const cpl_String& s) const {
    return (strcmp(str, s.str) > 0); 
}

//-----------------------------------------------------------------------------
bool cpl_String::operator == (const cpl_String& s) const { 
    return (strcmp(str, s.str) == 0); 
}

//-----------------------------------------------------------------------------
bool cpl_String::operator != (const cpl_String& s) const { 
    return (strcmp(str, s.str) != 0); 
}

//-----------------------------------------------------------------------------
cpl_String& cpl_String::operator += (const cpl_String& s) { 
    *this += s.str; return *this; 
}

//-----------------------------------------------------------------------------
cpl_String& cpl_String::operator = (cpl_String s) {
     return (*this = s.str); 
}
