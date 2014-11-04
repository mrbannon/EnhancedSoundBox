#ifndef __ESBACTORMANAGER_H__
#define __ESBACTORMANAGER_H__

#include <vector>
#include "ESBActor.h"
#include "../ESBAManager.h"
#include "../presentation/ESBRenderer.h"

/**
 * Manages the actors.
 */
class ESBActorManager: public ESBAManager
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:

        /**
         * Constructor.
         */
        ESBActorManager(ESBRenderer* apESBRenderer);


        /**
         * Destructor.
         */
        ~ESBActorManager(void);


        /**
         * Initialize.
         */
        void initialize(void);


        /**
         * Add actor.
         */
        void addActor(ESBActor* apESBActor);


        /**
         * Creates an actor and adds it to the list.
         */
        void createActor();


        /**
         * Updates actors.
         */
        void update(unsigned int aTimeIndex);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
    private:


        std::vector<ESBActor*> mvActorVector;
        ESBRenderer* mpESBRenderer;
};

#endif