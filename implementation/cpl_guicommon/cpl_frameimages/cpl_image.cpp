#include "cpl_frameimageincludes.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

///// static variable and function /////
static int s_image_id = 0;
static int s_invoke_imageId() {
    return ++s_image_id;
}

int s_issupported_stb_format(const char * ext) {
    if( !ext || ext[0] == 0 ) return 0;
    if( !strcmp(ext, "zip")  || !strcmp(ext, "ZIP") ) return 0;
    return 1;
}

//-----------------------------------------------------------------------------
//  cpl_Image
//-----------------------------------------------------------------------------
//
int cpl_Image::GetWidth() {
    return this->m_imageBitData.w;
}

//-----------------------------------------------------------------------------
int cpl_Image::GetHeight() {
    return this->m_imageBitData.h;
}

//-----------------------------------------------------------------------------
int cpl_Image::GetDepth()  {
    return this->m_imageBitData.ld;
}

//-----------------------------------------------------------------------------
unsigned char* cpl_Image::GetBufferBitsRGBA()  {
    return this->m_imageBitData.bits;
}

//-----------------------------------------------------------------------------
void cpl_Image::SetBitmap(unsigned char* bits, int w, int h, int ld) {
    //@@preconditions
    assert(bits && w > 0 && h > 0 && ld > 0);
    //@@end preconditions

    this->unload_bits();

    int sz = w*h*ld; assert(sz > 0);
    unsigned char * _buff = new unsigned char [sz]; assert(_buff);
    memcpy(_buff, bits, sz * sizeof(unsigned char));

    this->m_imageBitData.bits = _buff;
    this->m_imageBitData.w    = w;
    this->m_imageBitData.h    = h;
    this->m_imageBitData.ld   = ld;
}

//-----------------------------------------------------------------------------
void cpl_Image::Clone(cpl_Image * img) {
    //@@preconditions
    assert(img);
    //@@end preconditions

    if(img == this) return;

    //release and initialize
    this->initialize_info();
    this->unload_bits();

    //copy info. data
    this->m_imageInfo.id    = s_invoke_imageId();  //invoke a new unique id
    this->m_imageInfo.name  = img->m_imageInfo.name;
    this->m_imageInfo.fname = img->m_imageInfo.fname;
    this->m_imageInfo.path  = img->m_imageInfo.path;
    this->m_imageInfo.fmt   = img->m_imageInfo.fmt;

    //copy bit data
    int w  = img->m_imageBitData.w;
    int h  = img->m_imageBitData.h;
    int ld = img->m_imageBitData.ld;
    unsigned char * _bits = NULL;
    if( img->m_imageBitData.bits && w > 0 && h > 0 ) {
        int sz = w*h*ld; assert(sz > 0);
        _bits = new unsigned char [sz]; assert(_bits);
        memcpy(_bits, img->m_imageBitData.bits, sz*sizeof(unsigned char));
    }

    this->m_imageBitData.bits = _bits;
    this->m_imageBitData.w    = w;
    this->m_imageBitData.h    = h;
    this->m_imageBitData.ld   = ld;
}

//-----------------------------------------------------------------------------
int cpl_Image::IsLoaded() {
    unsigned char * bits = this->m_imageBitData.bits;
    int w = this->m_imageBitData.w;
    int h = this->m_imageBitData.h;

    return (bits && w > 0 && h > 0) ? 1 : 0;
}

//-----------------------------------------------------------------------------
void cpl_Image::Reset()
{
    this->m_imageInfo.name.clear();
    this->m_imageInfo.fname.clear();
    this->m_imageInfo.path.clear();
    this->m_imageInfo.fmt.clear();

    this->initialize_bitdata();
}

//-----------------------------------------------------------------------------
int cpl_Image::Load(const char * method) {
    if( method ) {
        assert(0);
        return 0;
    }

    if( this->IsLoaded() ) return 1;
    if(!s_issupported_stb_format(this->m_imageInfo.fmt.c_str()) ) return 0;

    int ret = this->load_bits();
    return ret;
}

//-----------------------------------------------------------------------------
int cpl_Image::UnLoad() {
    this->unload_bits();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int cpl_Image::load_bits() {
    const char * imgPath = this->m_imageInfo.path.c_str();
    if( !imgPath || imgPath[0] == 0 || cpl_SystemTools::CanAccessFile(imgPath) == 0 ) return 0;

    int w, h, ld, req_comp = 4;
    stbi_uc * bits = stbi_load(imgPath, &w, &h, &ld, req_comp);
    if( !bits ) return 0;

    assert(this->m_imageBitData.bits == NULL);

    int sz = w*h*ld; assert(sz > 0);
    unsigned char * _bits = new unsigned char [sz]; assert(_bits);
    memcpy(_bits, bits, sz*sizeof(unsigned char));

    this->m_imageBitData.bits = _bits;
    this->m_imageBitData.w    = w;
    this->m_imageBitData.h    = h;
    this->m_imageBitData.ld   = ld;

    stbi_image_free(bits);

    return 1;
}

//-----------------------------------------------------------------------------
void cpl_Image::unload_bits() {
    delete [] this->m_imageBitData.bits;
    this->m_imageBitData.bits = NULL;
    this->m_imageBitData.w    = 0;
    this->m_imageBitData.h    = 0;
    this->m_imageBitData.ld   = 0;
}

//-----------------------------------------------------------------------------
void cpl_Image::initialize_info() {
    this->m_imageInfo.id = 0;
    this->m_imageInfo.name.clear();
    this->m_imageInfo.fname.clear();
    this->m_imageInfo.path.clear();
    this->m_imageInfo.fmt.clear();
}

//-----------------------------------------------------------------------------
void cpl_Image::initialize_bitdata() {
    this->m_imageBitData.bits = NULL;
    this->m_imageBitData.w    = 0;
    this->m_imageBitData.h    = 0;
    this->m_imageBitData.ld   = 0;
}

//-----------------------------------------------------------------------------
cpl_Image::cpl_Image() {
    this->initialize_info();
    this->initialize_bitdata();
    this->m_imageInfo.id = s_invoke_imageId();  //assign a unique id for image
}

//-----------------------------------------------------------------------------
cpl_Image::~cpl_Image() {
    this->unload_bits();
}
