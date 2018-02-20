#ifndef CPL_IMAGE_H
#define CPL_IMAGE_H

class cpl_Image : public IImage {

public:
    /** load image */
    virtual int Load(const char * method = NULL);

    /** get the class type string */
    virtual const char * ClassType() { return "Image"; }

public:
    //image interface.
    /** get width */
    virtual int GetWidth();

    /** get height */
    virtual int GetHeight();

    /** get depth */
    virtual int GetDepth();

    /** get buffer bit */
    virtual unsigned char* GetBufferBitsRGBA();

public:
    /** id */
    int GetId() { return this->m_imageInfo.id; };

    /** name */
    void  SetName(const char* name) { this->m_imageInfo.name.assign(name); }
    const char* GetName() { return this->m_imageInfo.name.c_str(); }

    /** path */
    void  SetFullPath(const char* path) { this->m_imageInfo.path.assign(path); }
    const char* GetFullPath() { return this->m_imageInfo.path.c_str(); }

    /** format */
    void  SetFormat(const char* fmt) { this->m_imageInfo.fmt.assign(fmt); }
    const char* GetFormat() { return this->m_imageInfo.fmt.c_str(); }

public:
    /** bitmap buffer */
    void  SetBitmap(unsigned char* bits, int w, int h, int ld);
    unsigned char * GetBitmap() { return this->m_imageBitData.bits; }

    /** size */
    void  SetSize(int w, int h)   { this->m_imageBitData.w = w; this->m_imageBitData.h = h; }
    void  GetSize(int &w, int &h) { w = this->m_imageBitData.w; h = this->m_imageBitData.h; }

    /** Dimension */
    void  SetDim(int ld)  { this->m_imageBitData.ld = ld; }
    void  GetDim(int &ld) { ld = this->m_imageBitData.ld; }

public:
    /** unload image from memory */
    int UnLoad();

    /** check if icon is loaded into memory */
    int IsLoaded();

public:
    /** clean up */
    void Reset();

public:
    /** clone */
    void Clone(cpl_Image * img);

public:
    //constructor
    cpl_Image();

    //destructor.
    virtual ~cpl_Image();

protected:
    //load image bits in memory
    int load_bits();
    //unload image bits in memory
    void unload_bits();

protected:
    //protected variables   
    struct _fbImageInfo_s {
        int          id;        //image integer id
        std::string  name;      //image name(should be unique)

        std::string  fname;     //file name of image
        std::string  path;      //full path of image

        std::string  fmt;       //format of image file(like, "png", "xpm", even "zip")
    };
    _fbImageInfo_s   m_imageInfo;
   
    struct _fbImageBits_s {
        unsigned char * bits;   //loaded bits of image
        int w;                  //width of image
        int h;                  //height of image
        int ld;                 //dimension for image(like "png" is 4)
    };
    _fbImageBits_s   m_imageBitData;

private:
    //initialize _fbImageInfo_s structure
    void initialize_info();

    //initialize _fbImageBits_s structure
    void initialize_bitdata();
};

#endif //CPL_IMAGE_H
