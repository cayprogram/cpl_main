#include "cpl_frameimageincludes.h"

///// static variable and function /////
/*
 * cut off a sub-image from a large image
 */
static void s_getSubImageFromBitArray(unsigned char * obits,  /*large image*/
                                      int ow,                 /*width of large image*/
                                      int oh,                 /*height of large image*/
                                      int x,                  /*x offset*/
                                      int y,                  /*y offset*/
                                      int iw,                 /*width of cut-off image*/
                                      int ih,                 /*height of cut-off off image*/
                                      unsigned char * ibits   /*cut-off image*/
                                      ) {
    int line_size0 = ow*4;
    int line_size1 = iw*4;
    for (int i = 0; i < ih; i++) {
        unsigned char* p = &obits[(y+i)*line_size0+x*4];
        unsigned char* r = &ibits[i*line_size1];
        for (int j = 0; j < line_size1; j++) {
            r[j] = p[j];
        }
    }
}

#define BLD_ICONID(x,y) ((x)|((y)<<8))


//-----------------------------------------------------------------------------
//  class cpl_ImagePackageBlender
//-----------------------------------------------------------------------------
//
int cpl_ImagePackageBlender::Load(const char * method)
{
    //@@preconditions
    assert(method   != NULL);
    assert(this->m_subImage != NULL);
    //@@end preconditions

    this->m_subImage->Reset();

    int x, y;
    this->parse_method(method, x, y);
    assert(x >= 0 && y >= 0);

    int icnPos = BLD_ICONID(x,y);
    if( icnPos == -1 ) return 0;

    if( !this->parse_params(this->m_params.c_str()) ) return 0;

    if( !this->IsLoaded() ) { //load package image
        if( !this->load_bits() ) {
            assert(0);
            return 0;
        }
    }

    assert(this->m_imageBitData.bits);
    unsigned char * pkgBitmap = this->m_imageBitData.bits; assert(pkgBitmap);
    int pkgw = this->m_imageBitData.w;  assert(pkgw > 0);
    int pkgh = this->m_imageBitData.h;  assert(pkgh > 0);
    int ld   = this->m_imageBitData.ld; assert(ld > 0);

    int ix = icnPos & 0xff;         // 0 base
    int iy = (icnPos >> 8) & 0xff;  // 0 base

    int xoff = this->m_xoff;    assert(xoff >= 0);
    int yoff = this->m_yoff;    assert(yoff >= 0);
    int grid = this->m_grid;    assert(grid > 0);
    int cut  = this->m_cut;     assert(cut > 0);

    int ox = grid*ix + xoff;
    int oy = grid*iy + yoff;
    int ow = cut, oh = cut;
    unsigned char * obits = new unsigned char[ow*oh*ld]; assert(obits);
    s_getSubImageFromBitArray(pkgBitmap, pkgw, pkgh, ox, oy, ow, oh, obits);

    char imageName[256] = "";
    sprintf(imageName, "%s(%d,%d):%d", this->m_imageInfo.name.c_str(), x, y, this->m_subImage->GetId()); //create a new unique name for new sub-image
    this->m_subImage->SetName(imageName);

    this->m_subImage->SetBitmap(obits, ow, oh, ld);
    this->m_subImage->SetFormat(this->m_imageInfo.fmt.c_str());

    delete [] obits; obits = NULL;

    return 1;
}

//-----------------------------------------------------------------------------
void cpl_ImagePackageBlender::Clone(cpl_ImagePackageBlender * pkgImg)
{
    //@@preconditions
    assert(pkgImg != NULL);
    //@@end preconditions

    if(pkgImg == this) return;

    cpl_Image::Clone(pkgImg);

    this->m_xoff = pkgImg->m_xoff;
    this->m_yoff = pkgImg->m_yoff;
    this->m_grid = pkgImg->m_grid;
    this->m_cut  = pkgImg->m_cut;
}

//////////////////////////////////////////////////////////////////////////
void cpl_ImagePackageBlender::parse_method(const char * method, int &x, int &y)
{
    //@@preconditions
    assert(method != NULL);
    assert(strlen(method) > 0);
    //@@end preconditions

    //method string like: BLD_ICONID(5,8)
    x = y = -1;

    const char * leftBracket  = strchr (method, '(');  assert(leftBracket);
    const char * rightBracket = strrchr(method, ')');  assert(rightBracket);
    const char * comma        = strchr (method, ',');  assert(comma);

    int lx = comma - leftBracket - 1;     assert(lx > 0);
    int ly = rightBracket - comma - 1;    assert(ly > 0);

    char xstr[16], ystr[16];
    strncpy(xstr, leftBracket+1, lx); xstr[lx] = 0;
    strncpy(ystr, comma+1, ly);       ystr[ly] = 0;

    x = atoi(xstr);
    y = atoi(ystr);
}

//-----------------------------------------------------------------------------
int cpl_ImagePackageBlender::parse_params(const char * params)
// params string like: "5,10,21,16"
{
    //@@preconditions
    assert(params != NULL);
    assert(strlen(params) > 0);
    //@@end preconditions

    if( this->m_xoff >= 0 && this->m_yoff >= 0 && this->m_grid > 0 && this->m_cut > 0 ) return 1; //has been parsed

    int pms[4] = {-1, -1, 0, 0}, cnt = 0;
    char sep = ',';

    int slen = (int)strlen(params);
    char value[32];
    int  l;

    const char * prev = params;
    const char * curr = strchr(params, sep);
    while( curr != NULL ) {
        l = (int)(curr - prev); assert(l > 0);

        strncpy(value, prev, l);
        value[l] = 0;
        pms[cnt] = atoi(value); cnt++;

        prev = curr + 1;
        curr = strchr(prev, sep);
    }

    l = params + slen - prev;
    if( l > 0 ) {
        strncpy(value, prev, l);
        value[l] = 0;
        pms[cnt] = atoi(value); cnt++;
    }
    assert(cnt == 4);

    this->m_xoff = pms[0];
    this->m_yoff = pms[1];
    this->m_grid = pms[2];
    this->m_cut  = pms[3];

    return 1;
}

//-----------------------------------------------------------------------------
cpl_ImagePackageBlender::cpl_ImagePackageBlender() {
    this->m_xoff = -1;  this->m_yoff = -1;
    this->m_grid =  0;  this->m_cut  =  0;
}

//-----------------------------------------------------------------------------
cpl_ImagePackageBlender::~cpl_ImagePackageBlender() {
}
