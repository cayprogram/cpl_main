#ifndef CPL_DIRECTORY_H
#define CPL_DIRECTORY_H

class cpl_Directory : public cpl_Object {
	
public:
    /** create instance */
    static cpl_Directory *New();
    
    /** open the specified directory and load the names of the files */
    int Open(const char* dir);

    /** return the number of files in the current directory. */
    int GetNumberOfFiles() { return this->NumberOfFiles; }

    /** is path. */
    int FileIsDirectory(const char* name);
        
    /** return the file at the given index, the indexing is 0 based */
    const char* GetFile(int index);

    /** get the current working directory. */
    static const char* GetCurrentWorkingDirectory(char* buf, unsigned int len);

protected:
    // constructor.
    cpl_Directory();

    // destructor.
    virtual ~cpl_Directory() ;
  
    // clean varaiables. 
    void CleanUpFilesAndPath();

private:
    char* Path;   
    char** Files; 
    int NumberOfFiles;    
};

#endif //CPL_DIRECTORY_H
