#ifndef CPL_PLUGINTREENODE_H
#define CPL_PLUGINTREENODE_H

class cpl_PluginCodon;
class cpl_PluginTreeNode: public IPluginTreeNode, public cpl_Object {

public:
    /** create instance */
    static cpl_PluginTreeNode * New();

public:
    /** name */
    virtual void  SetName(const char* name);
    virtual const char* GetName();

    /** path */
    virtual void  SetPath(const char* path);
    virtual const char* GetPath();

    /** user data */
    virtual void  SetUserData(const void* userdata);
    virtual const void* GetUserData();

    /** codon */
    virtual void  SetCodon(IPluginCodon* codon);
    virtual IPluginCodon* GetCodon();

    /**set parent widget. */
    virtual void  SetParent(IPluginTreePath* parent);
    virtual IPluginTreePath* GetParent();
    
    /** is composite or not. */
    virtual int  IsComposite() { return 0; }

public:
    //inner structure.
    struct _fbNode_s {
        char* name;
        char* path;
        void* data;
        cpl_PluginCodon* codon;
        cpl_PluginTreePath* parent;
    };

    //constructor. 1
    cpl_PluginTreeNode();
    
    //constructor. 2
    cpl_PluginTreeNode(cpl_PluginTreePath* parent);

    //destructor.
    virtual ~cpl_PluginTreeNode();

    //protected variables   
    _fbNode_s nodeData;
};

#endif //CPL_PLUGINTREENODE_H
