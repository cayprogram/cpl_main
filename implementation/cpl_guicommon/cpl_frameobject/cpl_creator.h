#ifndef CPL_CREATOR_H
#define CPL_CREATOR_H

class cpl_ImplementationProxyCollection;
class cpl_Creator : public cpl_Object {
public:
    /** create function */
    static cpl_Creator * New();

public:
    /** create object */
    int CreateObject(REFDGUID clsId, void** ppv);

    /** create object */
    int CreateObject(const char* classId, void** ppv, int overrided = 1);
 
    /** insert implementation proxy */
    int InsertImplementationProxy(cpl_ImplementationProxy& proxy);

    /** remove implementation proxy */
    int RemoveImplementationProxy(cpl_ImplementationProxy& proxy);

public:
    /** add class override info */
    int InsertClassOverrideInfo(const char* classId, const char* newClassId);

    /** remove class override info */
    int RemoveClassOverrideInfo(const char* classId);

    /** find override info */
    int QueryClassOverrideInfo(const char* classId, const char*& newClassId);

protected:    
    // constructor 
    cpl_Creator();

    // destructor 
    virtual ~cpl_Creator();

    //protected variables.
    cpl_HashTableStringOneKey* pClassOverrideInfo;
    cpl_ImplementationProxyCollection* ImplementionProxyCollection;   
};

#endif //CPL_CREATOR_H
