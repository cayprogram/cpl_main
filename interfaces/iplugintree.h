#ifndef PLUGINTREEINTERFACE_H
#define PLUGINTREEINTERFACE_H

class IPluginTree {

public:
    /** get node in specific path */
    virtual IPluginTreePath* GetTreePath(const char* path) = 0;

    /** create path. */
    virtual IPluginTreePath* CreateTreePath(const char* path) = 0;
};

#endif //PLUGINTREEINTERFACE_H
