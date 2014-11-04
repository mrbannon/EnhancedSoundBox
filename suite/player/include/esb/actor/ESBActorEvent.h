#ifndef __ESBACTOREVENT_H__
#define __ESBACTOREVENT_H__


#include <vector>
#include "../ESBABase.h"


// Event types.
enum ESBACTOR_EVENT_TYPE
{
    MOVE,
    SET
};


// Event variables.
enum ESBACTOR_EVENT_VARIABLE
{
    PAN,
    PRESENCE,
    REGISTER
};


/**
 * Actor event.
 */
class ESBActorEvent: public ESBABase
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:

        /**
         * Constructor.
         */
        ESBActorEvent() 
        {
        };


        /**
         * Destructor.
         */
        ~ESBActorEvent();


        ESBACTOR_EVENT_TYPE type;
        ESBACTOR_EVENT_VARIABLE variable;
        float value0;
        float value1; // not used if SET
        unsigned int time0;
        unsigned int time1; // not used if SET
};

#endif