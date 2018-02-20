#ifndef OUTPUTMESSAGEINTERFACE_H
#define OUTPUTMESSAGEINTERFACE_H

class IOutputMessage {
public:
    /** output text */
    virtual void OutputText(const char* text) = 0;
};

#endif //OUTPUTMESSAGEINTERFACE_H
