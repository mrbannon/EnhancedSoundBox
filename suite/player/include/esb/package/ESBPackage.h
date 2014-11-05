#ifndef __ESBPACKAGE_H__
#define __ESBPACKAGE_H__


#include "../ESBABase.h"
#include "../actor/ESBActorManager.h"


/**
 * The package.
 */
class ESBPackage: public ESBABase
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
///////////////////////////////////////////////////////////////////////////////
    public:
        /**
         * Constructor.
         */
        ESBPackage(std::string aFilePath, ESBActorManager* apESBActorManager);


        /**
         * Destructor.
         */
        ~ESBPackage(void);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////////
    private:

        /**
         * Processes given line.
         */
        void processLine(std::string aLine);


        /**
         * Processes command and its parameters.
         */
        void processCommand(std::string aCommand, std::vector<std::string>* apParameters);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBERS
///////////////////////////////////////////////////////////////////////////////
    private:


        ESBActorManager* mpESBActorManager;

        std::string mFilePath;
        std::string mPackageName;
        std::string mAudioFilePath;
};

#endif