#include "cpl_wxguiobjectincludes.h"

//local includes.
#include "cpl_wxsystemmultifileio.h"

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

    wxFileDialog openFileDialog(win, _("Pick file"), _(directory), "", szFilter, wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
    openFileDialog.SetFilterIndex(initfilterIndex);
    int result = 0;
    switch(openFileDialog.ShowModal()) {
        case wxID_OK:
            {
                wxArrayString allPathes; 
                openFileDialog.GetPaths(allPathes); 
                if (allPathes.Count() > 0) {
                    cpl_MultiFileFilter::CleanupFilt();
                    for (size_t i = 0; i < allPathes.Count(); i++) {
                        wxString filePath = allPathes[i];
                        cpl_MultiFileFilter::FileFilter((char*)filePath.mb_str());
                    }
                    initfilterIndex = openFileDialog.GetFilterIndex();
                    cpl_SystemConfig::Instance()->SetWorkDirectory(cpl_MultiFileFilter::GetFilePath(0));
                }
                result = 1;
            }
            break;

    }
    return result;
}

//-----------------------------------------------------------------------------
int cpl_wxSystemMultiFileIO::OpenFile() {
    static char Filter[] = "LS-DYNA POST(d3plot;d3drlf;d3plotaa)|*.d3plot,d3plot,d3plot*,*.d3drlf,d3drlf,d3drlf*\tNASTRAN POST(*.pch, *.op2)|*.pch,*.op2";
    int fileOpenType = cpl_SystemConfig::Instance()->GetFileOpenType();
    int ret = SysDlgIOInFile(NULL, Filter, fileOpenType);
    if (ret == 1) {
        cpl_SystemConfig::Instance()->SetFileOpenType(fileOpenType);
    }
    return ret;
}

//-----------------------------------------------------------------------------
int cpl_wxSystemMultiFileIO::OpenFile(char* szFilter) {
    //@@preconditions
    assert(szFilter != NULL);
    //@@end preconditions

    int fileOpenType = 0;
    return SysDlgIOInFile(NULL, szFilter, fileOpenType);
}
