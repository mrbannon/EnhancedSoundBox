#ifndef __ESBABASE_H__
#define __ESBABASE_H__


#include <iostream>
#include <string>
#include <SDL.h>


struct vertex
{
    float x, y, z;
};

/**
 * ESB base class.
 */
class ESBABase
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:

        /**
         * Temporary.
         */
    //    virtual void temp(void) = 0;

    void logSDLError(std::ostream &os, const std::string &msg)
    {
        os << msg << " SDL ERROR: " << SDL_GetError() << std::endl;
    }
    void logMessage(std::ostream &os, const std::string &msg)
    {
        os << msg << std::endl;
    }
    void printSDLError(const std::string &msg)
    {
        logSDLError(std::cout, msg);
    }
    void printMessage(const std::string &msg)
    {
        logMessage(std::cout, msg);
    }
    void printErrorMessage(const std::string &msg)
    {
        logErrorMessage(std::cout, msg);
    }
    void logErrorMessage(std::ostream &os, const std::string &msg)
    {
        os <<  "ERROR: " << msg << std::endl;
    }
};

#endif