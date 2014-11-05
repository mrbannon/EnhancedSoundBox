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
         * Creates an actor and adds it to the list.
         */
        void createActor(std::string aId, std::string aName, std::string aTextureFilePath);


        /**
         * Updates actors.
         */
        void update(unsigned int aTimeIndex);


        /**
         * Set/move actor pan, presence, register.
         */
        void setActorEventPan(std::string aId, float aValue, unsigned int aTimeIndex);
        void setActorEventPresence(std::string aId, float aValue, unsigned int aTimeIndex);
        void setActorEventRegister(std::string aId, float aValue, unsigned int aTimeIndex);
        void moveActorEventPan(std::string aId, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1);
        void moveActorEventPresence(std::string aId, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1);
        void moveActorEventRegister(std::string aId, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////////
        /**
         * Add actor.
         */
        void addActor(ESBActor* apESBActor);


        /**
         * Find actor by ID.
         */
        ESBActor* findActorById(std::string aId);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBERS
///////////////////////////////////////////////////////////////////////////////
    private:


        std::vector<ESBActor*> mvActorVector;
        ESBRenderer* mpESBRenderer;
};

#endif