#include <cpl_guisystemincludes.h>
#include "cpl_application_.h"
#include "cpl_applicationrunner.h"

//-----------------------------------------------------------------------------
int main(int argc, char * * argv) {
    cpl_Application * theApp = new cpl_Application_;
    assert(theApp != NULL);
    
    cpl_ApplicationRunner runner(theApp);        
    if (runner.ProcessCommandLineArg(argc, argv))  {
        if (runner.Initialize(argc, argv) == 1) {
            runner.Running();
            runner.Cleanup();
        }    
    }
    cpl_Application::Delete();  
    return 0;
}

