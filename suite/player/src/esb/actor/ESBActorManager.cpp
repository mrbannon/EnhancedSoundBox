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
     

void ESBActorManager::addActor(ESBActor* apESBActor)
{
    if(apESBActor != nullptr)
    {
        mvActorVector.push_back(apESBActor);
    }
}


void ESBActorManager::createActor()
{
    // TEST0
    ESBActor* pTestActor = new ESBActor(50, 50);
    addActor(pTestActor);
    pTestActor->addSetEvent(ESBACTOR_EVENT_VARIABLE::PAN, -0.5f, 3000);
    pTestActor->addSetEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE, 1.0f, 5000);
    pTestActor->addSetEvent(ESBACTOR_EVENT_VARIABLE::REGISTER, 0.0f, 8000);
    pTestActor->addSetEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE, 0.5f, 10000);

    // TEST1
    ESBActor* pTestActor2 = new ESBActor(150, 80);
    addActor(pTestActor2);

    // PAN TEST.
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PAN,         0.0f, 0, 1.0f, 10000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PAN,         1.0f, 10000, 0.0f, 20000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PAN,         0.0f, 20000, -1.0f, 30000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PAN,         -1.0f, 30000, 0.0f, 40000);

    // PRESENCE TEST.
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE,    0.0f, 0, 0.5f, 10000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE,    0.5f, 10000, 1.0f, 20000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE,    1.0f, 20000, 0.5f, 30000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::PRESENCE,    0.5f, 30000, 0.0f, 40000);

    // REGISTER TEST.
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::REGISTER,    0.0f, 0, 0.5f, 10000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::REGISTER,    0.5f, 10000, 1.0f, 20000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::REGISTER,    1.0f, 20000, 0.5f, 30000);
    pTestActor2->addMoveEvent(ESBACTOR_EVENT_VARIABLE::REGISTER,    0.5f, 30000, 0.0f, 40000);
}


void ESBActorManager::update(unsigned int aTimeIndex)
{
    for(std::vector<ESBActor*>::const_iterator iterator = mvActorVector.begin(); iterator != mvActorVector.end(); ++iterator) 
    {
        ESBActor* pESBActor = *iterator;
        pESBActor->update(aTimeIndex);
    }
}


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////