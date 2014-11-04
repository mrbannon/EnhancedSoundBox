#ifndef __ESBDIRECTOR_H__
#define __ESBDIRECTOR_H__

#include "ESBABase.h"
#include "actor/ESBActorManager.h"
#include "presentation/ESBCamera.h"
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
         *
         * @param apESBRenderer renderer
         */
        ESBDirector(ESBRenderer* apESBRenderer);


        /**
         * Destructor.
         */
        ~ESBDirector(void);


        /**
         * Temporary.
         */
        void initialize(void);


        void run();


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
    private:

        void setCameraAtListenPoint();


        void setCameraOutside();


        ESBActorManager* mpESBActorManager;
        ESBCamera* mpESBCamera;
        ESBRenderer* mpESBRenderer;
        ESBStageManager* mpESBStageManager;
};

#endif