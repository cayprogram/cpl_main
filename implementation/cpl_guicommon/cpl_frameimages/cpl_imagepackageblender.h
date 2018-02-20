#ifndef CPL_IMAGEPACKAGEBLENDER_H
#define CPL_IMAGEPACKAGEBLENDER_H

//////////////////////////////////////////////////////////////////////////
class cpl_ImagePackageBlender : public cpl_ImagePackage {

public:
    /** load sub-image in package image to memory */
    virtual int Load(const char * method = NULL);

    /** get the class type string */
    virtual const char * ClassType() { return "blender-package"; }

public:
    /** set x offset */
    void SetXOffset(int xoff) { this->m_xoff = xoff; }
    /** get x offset */
    int  GetXOffset() { return this->m_xoff; }

    /** set y offset */
    void SetYOffset(int yoff) { this->m_yoff = yoff; }
    /** get y offset */
    int  GetYOffset() { return this->m_yoff; }

    /** set grid */
    void SetGrid(int grid) { this->m_grid = grid; }
    /** get grid */
    int  GetGrid() { return this->m_grid; }

    /** set cut */
    void SetCut(int cut) { this->m_cut = cut; }
    /** get cut */
    int  GetCut() { return this->m_cut; }

public:
    /** clone */
    void Clone(cpl_ImagePackageBlender * pkgImg);

protected:
    //parse method string
    void parse_method(const char * method, int &x, int &y);

    //parse params string
    int  parse_params(const char * params);

protected:
    //protected variables
    int   m_xoff;
    int   m_yoff;
    int   m_grid;
    int   m_cut;

public:
    //constructor
    cpl_ImagePackageBlender();

    //destructor.
    virtual ~cpl_ImagePackageBlender();
};

#endif //CPL_IMAGEPACKAGEBLENDER_H
