#include <cpl_guisystemincludes.h>
#include <cpl_controller/cpl_controllerapplicationincludes.h>
#include <cpl_guiengine/cpl_applicationguiengineimpincludes.h>

//-----------------------------------------------------------------------------
//  class cpl_Application_
//-----------------------------------------------------------------------------
//
void cpl_Application_::Initialize(int argc, char * * argv) {  
    //load object factory.
    new cpl_ApplicationControllerObjectFactory();

    //parent class.
    this->cpl_Application::Initialize(argc, argv);    
}

//-----------------------------------------------------------------------------
void cpl_Application_::Cleanup() {
    //parent class.
    this->cpl_Application::Cleanup();

    //cleanup resources.
    cpl_ControllerObjectFactory::Instance()->Delete();
    cpl_GUIObjectFactory::Delete();
}

//-----------------------------------------------------------------------------
cpl_Application_::cpl_Application_() {
    cpl_Application::SetApplication(this);
}
