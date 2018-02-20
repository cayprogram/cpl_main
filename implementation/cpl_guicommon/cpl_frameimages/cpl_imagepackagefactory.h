#ifndef CPL_IMAGEPACKAGE_FACTORY_H
#define CPL_IMAGEPACKAGE_FACTORY_H


//////////////////////////////////////////////////////////////////////////
class cpl_ImagePackageObjectFactory {
public:
    static cpl_ImagePackage * NewPackage(const char * type) {
        assert(type);

        if( !strcmp(type, "blender") ) {
            return new cpl_ImagePackageBlender();
        }else if( !strcmp(type, "zip") ) {
            return new cpl_ImagePackageZip();
        }else {
            assert(0);
            return NULL;
        }
    }

public:
    cpl_ImagePackageObjectFactory() {}
    virtual ~cpl_ImagePackageObjectFactory() {}
};

#endif //CPL_IMAGEPACKAGE_FACTORY_H
