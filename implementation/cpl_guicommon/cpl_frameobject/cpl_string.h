#ifndef CPL_STRING_H
#define CPL_STRING_H

class cpl_String {

public:
    /** Default constructor: sets to empty string ("") */
    cpl_String();

    /** Allocates the string to be of length \b len. Does not set the buffer to any initial value */
    cpl_String( unsigned int len );

    /** String copy constructor */
    cpl_String( const char *s );

    /** Copy constructor */
    cpl_String( const cpl_String& s );

    /** Default destructor */
    ~cpl_String();

    /** copy operator */
    cpl_String& operator =( const char *s );

    /** copy operator */
    cpl_String& operator =( cpl_String s );

    /** concatenate assignment operator */
    cpl_String& operator +=( const char *s );

    /** concatenate assignment operator */
    cpl_String& operator +=( const cpl_String& s );

    /** return the indicated substring of this string */
    cpl_String substr( int pos, int len ) const;

public:
    /** a c-style nul terminated pointer to the string */
    char* operator() ();

    /** a c-style nul terminated pointer to the string */
    const char* c_str() const;

    /** array operator */
    char& operator [](int i);

    /** array operator */
    char  operator [](int i) const;

    /** alias for the = operator */
    void copy( const cpl_String& s );

    /** alias for the = operator */
    void copy( const char *s );

    /** convert this string to uppercase */
    void upcase();

    /** convert this string to lowercase */
    void downcase();

    /** trim */
    void trim();

    /** character c to the end of the string */
    void push_back( char c );

    /** copy the substring of s to this string */
    void copy( const cpl_String& s, unsigned int start, unsigned int len ) ;

    /** copy the substring of s to this string */
    void copy( const char *s, unsigned int start, unsigned int len );

    /** how long the string is */
    int size() const;

    /** return the first index of character c in this string, or -1 if c is not in this string */
    int find( char c ) const;

    /** return the first index of character c in this string, or -1 if c is not in this string */
    int find( char c, int pos) const;

    /** return the last index of character c in this string, or -1 if c is not in this string */
    int rfind( char c ) const;

    /** return 0 if this string is equal to s, -1 if this string is lexigraphically less than \b s, 1 if this string is lexigraphically greater than s (uses c-std function strcmp ) */
    int compare( const cpl_String &s ) const;

    /** same as compare(), except ignores the case of the string */
    int casecompare( const cpl_String &s ) const;

    /** less-than operator */
    bool operator <( const cpl_String& s ) const;

    /** greater-than operator */
    bool operator >( const cpl_String& s ) const;

    /** equality operator */
    bool operator ==( const cpl_String& s ) const;

    /** inequality operator */
    bool operator !=( const cpl_String& s ) const;

private:
    char *str;
};

#endif //CPL_STRING_H


