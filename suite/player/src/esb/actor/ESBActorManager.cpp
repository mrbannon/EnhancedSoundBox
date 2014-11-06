#include "esb/actor/ESBActorManager.h"


///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
ESBActorManager::ESBActorManager(ESBRenderer* apESBRenderer):
    mvActorVector(),
    mpESBRenderer(apESBRenderer)
{
}


ESBActorManager::~ESBActorManager(void)
{
    mvActorVector.clear(); // this calls the destructor on all contents
    mpESBRenderer = nullptr; // just null it...it should be destroyed elsewhere
}


void ESBActorManager::initialize(void)
{
    mpESBRenderer->setActorVector(&mvActorVector);
}


void ESBActorManager::createActor(std::string aId, std::string aName, std::string aTextureName)
{
    // Get the texture.
    unsigned int textureId = mpESBRenderer->getTextureIdByName(aTextureName);

    // Create the actor.
    ESBActor* pTestActor = new ESBActor(200, 200, aId, aName, textureId);

    // Push the actor.
    addActor(pTestActor);
}


void ESBActorManager::update(unsigned int aTimeIndex)
{
    for(std::vector<ESBActor*>::const_iterator iterator = mvActorVector.begin(); iterator != mvActorVector.end(); ++iterator) 
    {
        ESBActor* pESBActor = *iterator;
        pESBActor->update(aTimeIndex);
    }
}


void ESBActorManager::setActorEventPan(std::string aId, float aValue, unsigned int aTimeIndex)
{
    ESBActor* pESBActor = findActorById(aId);
    pESBActor->addSetEvent(ESBACTOR_EVENT_VARIABLE::PAN, aValue, aTimeIndex);
}


void ESBActorManager::setActorEventPresence(std::string aId, float aValue, unsigned int aTimeIndex)
{
    ESBActor* pESBActor = findActorById(aId);
    pESBActor->addSetEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE, aValue, aTimeIndex);
}


void ESBActorManager::setActorEventRegister(std::string aId, float aValue, unsigned int aTimeIndex)
{
    ESBActor* pESBActor = findActorById(aId);
    pESBActor->addSetEvent(ESBACTOR_EVENT_VARIABLE::REGISTER, aValue, aTimeIndex);
}


void ESBActorManager::moveActorEventPan(std::string aId, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1)
{
    ESBActor* pESBActor = findActorById(aId);
    pESBActor->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PAN, aValue0, aTimeIndex0, aValue1, aTimeIndex1);
}


void ESBActorManager::moveActorEventPresence(std::string aId, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1)
{
    ESBActor* pESBActor = findActorById(aId);
    pESBActor->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE, aValue0, aTimeIndex0, aValue1, aTimeIndex1);
}


void ESBActorManager::moveActorEventRegister(std::string aId, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1)
{
    ESBActor* pESBActor = findActorById(aId);
    pESBActor->addMoveEvent(ESBACTOR_EVENT_VARIABLE::REGISTER, aValue0, aTimeIndex0, aValue1, aTimeIndex1);
}


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
void ESBActorManager::addActor(ESBActor* apESBActor)
{
    if(apESBActor != nullptr)
    {
        mvActorVector.push_back(apESBActor);
    }
}


ESBActor* ESBActorManager::findActorById(std::string aId)
{
    for(std::vector<ESBActor*>::const_iterator iterator = mvActorVector.begin(); iterator != mvActorVector.end(); ++iterator) 
    {
        ESBActor* pESBActor = *iterator;
        if(pESBActor->getId() == aId)
        {
            return pESBActor;
        }
    }
    return nullptr;
}