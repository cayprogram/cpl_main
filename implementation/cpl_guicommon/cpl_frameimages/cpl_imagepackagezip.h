#ifndef CPL_IMAGEPACKAGEZIP_H
#define CPL_IMAGEPACKAGEZIP_H

//////////////////////////////////////////////////////////////////////////
class cpl_ImagePackageZip : public cpl_ImagePackage {

public:
    /** load sub-image in package image to memory */
    virtual int Load(const char * method = NULL);

    /** get the class type string */
    virtual const char * ClassType() { return "zip-package"; }

public:
    /** clone */
    void Clone(cpl_ImagePackageZip * zipPkg);

protected:
    //parse method string
    int extract_zip_file(const char * fileInZip);

protected:
    //protected variables

public:
    //constructor
    cpl_ImagePackageZip();

    //destructor.
    virtual ~cpl_ImagePackageZip();
};

#endif //CPL_IMAGEPACKAGEZIP_H
