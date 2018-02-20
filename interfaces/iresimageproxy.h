#ifndef IRESOURCEIMAGEPROXYINTERFACE_H
#define IRESOURCEIMAGEPROXYINTERFACE_H

//-----------------------------------------------------------------------------
// class IImage
//-----------------------------------------------------------------------------
//
class IImage {

public:
    /** get width */
    virtual int GetWidth() = 0;

    /** get height */
    virtual int GetHeight() = 0;

    /** get depth */
    virtual int GetDepth() = 0;

    /** get buffer bit */
    virtual unsigned char* GetBufferBitsRGBA() = 0;
};


//-----------------------------------------------------------------------------
// class IResImageProxy
//-----------------------------------------------------------------------------
//
class IResImageProxy {

public:
    /** get image bitmap memory buffer */
    virtual IImage* GetImage(const char *iconId) = 0;
};

#endif //IRESOURCEIMAGEPROXYINTERFACE_H
