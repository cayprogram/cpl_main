#ifndef CPL_ICONMANAGER_H
#define CPL_ICONMANAGER_H

//////////////////////////////////////////////////////////////////////////
class cpl_IconManager {
public:
    /** add icon */
    int AddIcon(const char * iconId, const char * imageId);

    /** delete icon */
    int DeleteIcon(const char * iconId);

public:
    /** get icon*/
    const char * GetIcon(const char * iconId);

public:
    //constructor
    cpl_IconManager();

    //destructor.
    virtual ~cpl_IconManager();

protected:
    //protected variables
    std::map<std::string, std::string> * m_iconMap;

private:
    //find icon
    const char * find_icon(const char * iconId); 

    //cleanup map
    void cleanup_map();
};

#endif //CPL_ICONMANAGER_H
