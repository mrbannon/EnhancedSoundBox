#include "esb/actor/ESBActor.h"


const unsigned short ESBActor::INDICIES[] =  {0, 1, 2,
                                              2, 3, 0};


///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
ESBActor::ESBActor(const unsigned int aHeight, 
                   const unsigned int aWidth):
    mHeight(aHeight),
    mWidth(aWidth),
    mVisible(true),
    mVerticies(),
    mRegister(0.5f),
    mPan(0.0f),
    mPresence(0.5f),
    mvActorEventVectorPan(),
    mvActorEventVectorPresence(),
    mvActorEventVectorRegister(),
    mActorEventVectorPanIndex(0),
    mActorEventVectorPresenceIndex(0),
    mActorEventVectorRegisterIndex(0)
{
    generateVerticies();
}


ESBActor::~ESBActor(void)
{
}


void ESBActor::setRegister(float aRegister)
{
    mRegister = aRegister > 1.0f ? 1.0f : (aRegister < 0.0f ? 0.0f : aRegister);
}


void ESBActor::setPan(float aPan)
{
    mPan = aPan > 1.0f ? 1.0f : (aPan < -1.0f ? -1.0f : aPan);
}


void ESBActor::setPresence(float aPresence)
{
    mPresence = aPresence > 1.0f ? 1.0f : aPresence;
}


void ESBActor::update(unsigned int aTimeIndex)
{
    executeNextEvent(&mvActorEventVectorPan, &mActorEventVectorPanIndex, aTimeIndex);
    executeNextEvent(&mvActorEventVectorPresence, &mActorEventVectorPresenceIndex, aTimeIndex);
    executeNextEvent(&mvActorEventVectorRegister, &mActorEventVectorRegisterIndex, aTimeIndex);
}

void ESBActor::addSetEvent(ESBACTOR_EVENT_VARIABLE aVariable, float aValue, unsigned int aTimeIndex)
{
    ESBActorEvent* pESBActorEvent = new ESBActorEvent();
    pESBActorEvent->type = ESBACTOR_EVENT_TYPE::SET;
    pESBActorEvent->variable = aVariable;
    pESBActorEvent->value0 = aValue;
    pESBActorEvent->time0 = aTimeIndex;
    switch(pESBActorEvent->variable)
    {
        case ESBACTOR_EVENT_VARIABLE::PAN:
        {
            printMessage("pan event added");
            mvActorEventVectorPan.push_back(pESBActorEvent);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::PRESENCE:
        {
            printMessage("presence event added");
            mvActorEventVectorPresence.push_back(pESBActorEvent);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::REGISTER:
        {
            printMessage("register event added");
            mvActorEventVectorRegister.push_back(pESBActorEvent);
            break;
        }

        default:
        {
            printErrorMessage("unknown event variable");
        }
    }
}


void ESBActor::addMoveEvent(ESBACTOR_EVENT_VARIABLE aVariable, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1)
{
    ESBActorEvent* pESBActorEvent = new ESBActorEvent();
    pESBActorEvent->type = ESBACTOR_EVENT_TYPE::MOVE;
    pESBActorEvent->variable = aVariable;
    pESBActorEvent->value0 = aValue0;
    pESBActorEvent->time0 = aTimeIndex0;
    pESBActorEvent->value1 = aValue1;
    pESBActorEvent->time1 = aTimeIndex1;
    switch(pESBActorEvent->variable)
    {
        case ESBACTOR_EVENT_VARIABLE::PAN:
        {
            printMessage("pan event added");
            mvActorEventVectorPan.push_back(pESBActorEvent);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::PRESENCE:
        {
            printMessage("presence event added");
            mvActorEventVectorPresence.push_back(pESBActorEvent);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::REGISTER:
        {
            printMessage("register event added");
            mvActorEventVectorRegister.push_back(pESBActorEvent);
            break;
        }

        default:
        {
            printErrorMessage("unknown event variable");
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
void ESBActor::generateVerticies()
{
    mVerticies[0].x = -0.5f * getWidth();
    mVerticies[0].y = -0.5f * getHeight();
    mVerticies[0].z = 0.0f;
    mVerticies[1].x = 0.5f * getWidth();
    mVerticies[1].y = -0.5f * getHeight();
    mVerticies[1].z = 0.0f;
    mVerticies[2].x = 0.5f * getWidth();
    mVerticies[2].y = 0.5f * getHeight();
    mVerticies[2].z = 0.0f;
    mVerticies[3].x = -0.5f * getWidth();
    mVerticies[3].y = 0.5f * getHeight();
    mVerticies[3].z = 0.0f;
}


void ESBActor::executeNextEvent(std::vector<ESBActorEvent*>* apVector, unsigned int* apIndex, unsigned int aTimeIndex)
{
    updateIndexToNextEvent(apVector, apIndex, aTimeIndex);
    if((*apIndex) < apVector->size())
    {
        ESBActorEvent* pCurrentEvent = apVector->at(*apIndex);
        if(aTimeIndex >= pCurrentEvent->time0)
        {
            switch(pCurrentEvent->type)
            {
                case ESBACTOR_EVENT_TYPE::MOVE:
                {
                    executMoveEvent(pCurrentEvent, aTimeIndex);
                    (*apIndex) += pCurrentEvent->time1 >= aTimeIndex ? 0 : 1;
                    break;
                }

                case ESBACTOR_EVENT_TYPE::SET:
                {
                    executSetEvent(pCurrentEvent, aTimeIndex);
                    (*apIndex)++;
                    break;
                }

                default:
                {
                    printErrorMessage("unknown event type");
                }
            }   
        }
    }
}


void ESBActor::updateIndexToNextEvent(std::vector<ESBActorEvent*>* apVector, unsigned int* apIndex, unsigned int aTimeIndex)
{
    if((*apIndex) < apVector->size())
    {
        ESBActorEvent* pCurrentEvent = nullptr;
        bool found = false;
        while(!found)
        {
            pCurrentEvent = apVector->at(*apIndex);

            // Is there another event in the vector?
            if((*apIndex) + 1  < apVector->size())
            {
                // There is.  Should we use it?
                ESBActorEvent* pNextEvent = apVector->at((*apIndex) + 1);
                if(aTimeIndex >= pNextEvent->time0)
                {
                    // Yes we should.  Update.
                    (*apIndex)++;
                }
                else
                {
                    // Nope, this is the latest event.
                    found = true;
                }
            }
            else
            {
                // There isn't another event.  We deal with this one.
                found = true;
            }
        }
    }
}


void ESBActor::executSetEvent(ESBActorEvent* apEvent, unsigned int aTimeIndex)
{
    printMessage("executing set event at time index " + std::to_string(aTimeIndex));
    switch(apEvent->variable)
    {
        case ESBACTOR_EVENT_VARIABLE::PAN:
        {
            setPan(apEvent->value0);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::PRESENCE:
        {
            setPresence(apEvent->value0);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::REGISTER:
        {
            setRegister(apEvent->value0);
            break;
        }

        default:
        {
            printErrorMessage("unknown event variable");
        }
    }
    printMessage("done executing event");
}


void ESBActor::executMoveEvent(ESBActorEvent* apEvent, unsigned int aTimeIndex)
{
    printMessage("executing move event at time index " + std::to_string(aTimeIndex));
    unsigned int eventDuration = apEvent->time1 - apEvent->time0;
    float eventProgress = (aTimeIndex - apEvent->time0) / (float)eventDuration;
    float eventValueDelta = apEvent->value1 - apEvent->value0;
    float eventValueProgress = eventProgress * eventValueDelta;
    float value = apEvent->value0 + eventValueProgress;
    switch(apEvent->variable)
    {
        case ESBACTOR_EVENT_VARIABLE::PAN:
        {
            setPan(value);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::PRESENCE:
        {
            setPresence(value);
            break;
        }

        case ESBACTOR_EVENT_VARIABLE::REGISTER:
        {
            setRegister(value);
            break;
        }

        default:
        {
            printErrorMessage("unknown event variable");
        }
    }
}