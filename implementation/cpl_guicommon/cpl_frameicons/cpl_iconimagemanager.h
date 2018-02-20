#ifndef CPL_ICONIMAGEMANAGER_H
#define CPL_ICONIMAGEMANAGER_H

//////////////////////////////////////////////////////////////////////////
class cpl_IconImageManager : public cpl_ImageManager {

public:
    /** add image */
    virtual void AddImage(const char * ImageId, cpl_Image * image);

public:
    //constructor
    cpl_IconImageManager() {}

    //destructor.
    virtual ~cpl_IconImageManager() {}
};

#endif //CPL_ICONIMAGEMANAGER_H
