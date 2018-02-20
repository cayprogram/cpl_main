#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxsystemfileio.h"

//-----------------------------------------------------------------------------
static int SysDlgIOInFile(char *initdirectory, char * szFilter, int& initfilterIndex) {
    //@@preconditions.
    assert(szFilter != NULL);
    //@@end preconditions

    const char *dir = NULL;
    if (initdirectory != NULL) {
        dir = initdirectory;
    }
    else {
        cpl_SystemConfig::Instance()->GetWorkDirectory(dir);
    }

    wxFrame* win = (wxFrame*)cpl_SystemConfig::Instance()->GetMainWindowHandler();
    assert  (win != NULL);

    char directory[512];
    memset(directory, 0, sizeof(char)*512);
    strcpy(directory, dir);

    wxFileDialog openFileDialog(win, _("Pick file"), _(directory), "", szFilter, wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    openFileDialog.SetFilterIndex(initfilterIndex);
    int result = 0;
    switch(openFileDialog.ShowModal()) {
        case wxID_OK:
            {
                wxString filePath = openFileDialog.GetPath();
                initfilterIndex = openFileDialog.GetFilterIndex();
                cpl_FileFilter::FileFilter((char*)filePath.mb_str());
                cpl_SystemConfig::Instance()->SetWorkDirectory(cpl_FileFilter::GetFilePath());
                result = 1;
            }
            break;

    }
    return result;
}

//-----------------------------------------------------------------------------
static int SysDlgIOOutFile(char *initdirectory, char * szFilter, int& initfilterIndex) {
    //@@preconditions.
    assert(szFilter != NULL);
    //@@end preconditions

    const char *dir = NULL;
    if (initdirectory != NULL) {
        dir = initdirectory;
    }
    else {
        cpl_SystemConfig::Instance()->GetWorkDirectory(dir);
    }

    wxFrame* win = (wxFrame*)cpl_SystemConfig::Instance()->GetMainWindowHandler();
    assert  (win != NULL);

    char directory[512];
    memset(directory, 0, sizeof(char)*512);
    strcpy(directory, dir);

    wxFileDialog saveFileDialog(win, _("Save file"), _(directory), "", szFilter, wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    saveFileDialog.SetFilterIndex(initfilterIndex);
    int result = 0;
    switch(saveFileDialog.ShowModal()) {
        case wxID_OK:
            {
                wxString filePath = saveFileDialog.GetPath();
                initfilterIndex = saveFileDialog.GetFilterIndex();
                assert(initfilterIndex >= 0);
                cpl_FileFilter::FileFilter((char*)filePath.mb_str());
                cpl_SystemConfig::Instance()->SetWorkDirectory(cpl_FileFilter::GetFilePath());
                result = 1;
            }
            break;

    }
    return result;
}

//-----------------------------------------------------------------------------
static int SysDlgIOInDirectory(char *initdirectory) {
    //@@preconditions.
    //@@end preconditions
    return 0;
}

//-----------------------------------------------------------------------------
static int SysDlgIOOutDirectory(char *initdirectory) {
    //@@preconditions.
    //@@end preconditions
    return 0;
}

//-----------------------------------------------------------------------------
int cpl_wxSystemFileIO::OpenFile() {
    static char Filter[] = "Demo Database|*.db";
    int fileOpenType = cpl_SystemConfig::Instance()->GetFileOpenType();
    int ret = SysDlgIOInFile(NULL, Filter, fileOpenType);
    if (ret == 1) {
        cpl_SystemConfig::Instance()->SetFileOpenType(fileOpenType);
    }
    return ret;
}

//-----------------------------------------------------------------------------
int cpl_wxSystemFileIO::OpenFile(char * szFilter, int & fileOpenType) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions

    return SysDlgIOInFile(NULL, szFilter, fileOpenType);
}

//-----------------------------------------------------------------------------
int cpl_wxSystemFileIO::SaveFile(char* szFilter, int & fileOpenType) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions
    
    return SysDlgIOOutFile(NULL, szFilter, fileOpenType);
}

//-----------------------------------------------------------------------------
int cpl_wxSystemFileIO::OpenDirectory() {
    return SysDlgIOInDirectory(NULL);
}

//-----------------------------------------------------------------------------
int cpl_wxSystemFileIO::SaveDirectory() {
    return SysDlgIOOutDirectory(NULL);
}
