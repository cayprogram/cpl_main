#ifndef CPL_IMAGEMANAGER_H
#define CPL_IMAGEMANAGER_H

//////////////////////////////////////////////////////////////////////////
class cpl_ImageManager {

public:
    /** add image */
    virtual void AddImage(const char * ImageId, cpl_Image * image);

    /** delete image */
    void DeleteImage(const char * ImageId);

public:
    /** get image*/
    cpl_Image * GetImage(const char * ImageId);

public:
    //constructor
    cpl_ImageManager();

    //destructor.
    virtual ~cpl_ImageManager();

protected:
    //protected variables
    std::map<std::string, cpl_Image *> * m_imageMAP;

protected:
    //find out image by name
    cpl_Image * find_image(const char * ImageId); 

    //cleanup image storage map
    void cleanup_map();

    //delete image
    void delete_image(cpl_Image * img);
};

#endif //CPL_IMAGEMANAGER_H
