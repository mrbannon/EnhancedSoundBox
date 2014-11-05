#ifndef __ESBDIRECTOR_H__
#define __ESBDIRECTOR_H__

#include "ESBABase.h"
#include "actor/ESBActorManager.h"
#include "presentation/ESBRenderer.h"
#include "stage/ESBStageManager.h"

/**
 * ESB Director
 */
class ESBDirector: public ESBABase
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:


        /**
         * Constructor.
         */
        ESBDirector(ESBRenderer* apESBRenderer, ESBActorManager* apESBActorManager);


        /**
         * Destructor.
         */
        ~ESBDirector(void);


        /**
         * Initialize.
         */
        void initialize(void);


        /**
         * Run.
         */
        void run();


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
    private:

        void setCameraAtListenPoint();


        void setCameraOutside();


        ESBActorManager* mpESBActorManager;
        ESBRenderer* mpESBRenderer;
        ESBStageManager* mpESBStageManager;
};

#endif