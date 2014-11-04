#ifndef __ESBACTOR_H__
#define __ESBACTOR_H__


#include <vector>
#include "ESBActorEvent.h"
#include "../ESBABase.h"


/**
 * The base actor.
 *
 * Actor events.  For movements, to keep a coordinate the same, just use "-".
 *
 *
 * pan: [-1.0f, 1.0f]
 * presence: [0.0f, 1.0f]
 * register: [0.0f, 1.0f]
 *
 * <time_index> is ms from start
 *
 * Example:
 *
 * actor_event_set_pan:        <identifier> <pan> <time_index>
 * actor_event_set_presence:   <identifier> <presence> <time_index>
 * actor_event_set_register:   <identifier> <register> <time_index>
 *
 * actor_event_move_pan:        <identifier> <pan0> <pan1> <time_index0> <time_index1>
 * actor_event_move_presence:   <identifier> <presence0> <presence1> <time_index0> <time_index1>
 * actor_event_move_register:   <identifier> <register0> <register1> <time_index0> <time_index1>
 * 
 * actor_active: <0,1> (active by default)
 *
 */
class ESBActor: public ESBABase
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:

        /**
         * Constructor.
         */
        ESBActor(const unsigned int aHeight, 
                 const unsigned int aWidth);


        /**
         * Destructor.
         */
        ~ESBActor(void);


        void setRegister(float aRegister);


        void setPan(float aPan);


        void setPresence(float aPresence);


        void update(unsigned int aTimeIndex);


        void addSetEvent(ESBACTOR_EVENT_VARIABLE aVariable, float aValue, unsigned int aTimeIndex);


        void addMoveEvent(ESBACTOR_EVENT_VARIABLE aVariable, float aValue0, unsigned int aTimeIndex0, float aValue1, unsigned int aTimeIndex1);


        inline const unsigned short* getIndicies() const { return INDICIES; }

        inline unsigned int getHeight() { return mHeight; };
        inline unsigned int getWidth() { return mWidth; };

        inline bool isVisible() { return mVisible; };

        inline vertex* getVerticies() { return mVerticies; }

        inline float getRegister() { return mRegister; } // 0 to 1
        inline float getPan() { return mPan; }; // -1 to 1
        inline float getPresence() { return mPresence; };  // 0 to 1


///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////////
    private:


        void generateVerticies();

        void executeNextEvent(std::vector<ESBActorEvent*>* apVector, unsigned int* apIndex, unsigned int aTimeIndex);

        void executSetEvent(ESBActorEvent* apEvent, unsigned int aTimeIndex);

        void executMoveEvent(ESBActorEvent* apEvent, unsigned int aTimeIndex);

        void updateIndexToNextEvent(std::vector<ESBActorEvent*>* apVector, unsigned int* apIndex, unsigned int aTimeIndex);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBERS
///////////////////////////////////////////////////////////////////////////////
    private:

        static const unsigned short INDICIES[];

        unsigned int mHeight;
        unsigned int mWidth;

        bool mVisible;

        vertex mVerticies[8];

        float mRegister;
        float mPan;
        float mPresence;

        std::vector<ESBActorEvent*> mvActorEventVectorPan;
        std::vector<ESBActorEvent*> mvActorEventVectorPresence;
        std::vector<ESBActorEvent*> mvActorEventVectorRegister;
        unsigned int mActorEventVectorPanIndex;
        unsigned int mActorEventVectorPresenceIndex;
        unsigned int mActorEventVectorRegisterIndex;
};

#endif