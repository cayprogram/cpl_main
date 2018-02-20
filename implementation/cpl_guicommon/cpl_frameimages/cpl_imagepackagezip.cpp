#include "cpl_frameimageincludes.h"
#include "stb_image.h"
// #include "libzipex.h"
#include "libzippp.h"
using namespace libzippp;

///// static variable and function /////


//-----------------------------------------------------------------------------
//  class cpl_ImagePackageZip
//-----------------------------------------------------------------------------
//
int cpl_ImagePackageZip::Load(const char * method)
{
    //@@preconditions
    assert(method   != NULL);
    assert(this->m_subImage != NULL);
    //@@end preconditions

    this->m_subImage->Reset();

    int ret = this->extract_zip_file(method);
    return ret;
}

//-----------------------------------------------------------------------------
void cpl_ImagePackageZip::Clone(cpl_ImagePackageZip * zipPkg)
{
    //@@preconditions
    assert(zipPkg != NULL);
    //@@end preconditions

    if(zipPkg == this) return;

    cpl_Image::Clone(zipPkg);
}

//////////////////////////////////////////////////////////////////////////
int cpl_ImagePackageZip::extract_zip_file(const char * fileInZip)
{
    //@@preconditions
    assert(fileInZip != NULL);
    //@@end preconditions

    const char * zipFilePath = this->m_imageInfo.path.c_str(); assert(zipFilePath);
    if( cpl_SystemTools::CanAccessFile(zipFilePath) == 0 ) return 0;

    //[using libzipEx library]
/*
    libzipEx zf;
    int iret = zf.OpenZipFile(zipFilePath, ARCHIVEZIP_READONLY);
    if (iret != ZIPARCHIVE_SUCCESS) return 0;

    unsigned char * imgBits = NULL;
    uzip64_t len = 0;
    iret = zf.GetArchive(fileInZip, imgBits, len);
    if (iret != ZIPARCHIVE_SUCCESS) return 0;

    int ow, oh, ld, req_comp = 4;
    stbi_uc * obits = stbi_load_from_memory((stbi_uc *)imgBits, (int)len, &ow, &oh, &ld, req_comp);
    if( !obits ) {
        zf.CloseZipFile();
        return 0;
    }
    zf.CloseZipFile();
*/

    //[using libzippp library]
    ZipArchive zf(zipFilePath);
    zf.open(ZipArchive::READ_ONLY);

    char * imgBits = (char *)zf.readEntry(fileInZip, true); //raw access
    ZipEntry imgEntry = zf.getEntry(fileInZip);
    int len = (int)imgEntry.getSize();

    int ow, oh, ld, req_comp = 4;
    stbi_uc * obits = stbi_load_from_memory((stbi_uc *)imgBits, len, &ow, &oh, &ld, req_comp);
    if( !obits ) {
        zf.close();
        return 0;
    }
    zf.close();


    char imageName[256] = "";
    sprintf(imageName, "%s_sub:%d", this->m_imageInfo.name.c_str(), this->m_subImage->GetId()); //create a new unique name for new sub-image
    this->m_subImage->SetName(imageName);
    //set image bits
    this->m_subImage->SetBitmap(obits, ow, oh, ld);
    //set image package format(parsed by file extension)
    cpl_FileFilter::FileFilter((char *)fileInZip);
    char * ext = cpl_FileFilter::GetFileExt();  assert(ext);
    this->m_subImage->SetFormat(ext);

    stbi_image_free(obits);

    return 1;
}

//-----------------------------------------------------------------------------
cpl_ImagePackageZip::cpl_ImagePackageZip() {
}

//-----------------------------------------------------------------------------
cpl_ImagePackageZip::~cpl_ImagePackageZip() {
}
