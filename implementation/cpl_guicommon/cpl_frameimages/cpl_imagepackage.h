#ifndef CPL_IMAGEPACKAGE_H
#define CPL_IMAGEPACKAGE_H

//////////////////////////////////////////////////////////////////////////
class cpl_ImagePackage : public cpl_Image {

public:
    /** load sub-image in package image to memory */
    virtual int Load(const char * method = NULL) = 0;

    /** get the class type string */
    virtual const char * ClassType() { return "package"; }

public:
    /** set sub-image container */
    void SetSubImage(cpl_Image * image) { this->m_subImage = image; }

    /** set parameters */
    void SetParams(const char * params) { this->m_params.assign(params); }

protected:
    //protected variables
    cpl_Image *  m_subImage;

    std::string m_params;

public:
    //constructor
    cpl_ImagePackage() : m_subImage(NULL) { this->m_params.clear(); }

    //destructor.
    virtual ~cpl_ImagePackage() {}
};

#endif //CPL_IMAGEPACKAGE_H
