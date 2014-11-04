#ifndef __ESBSTAGEMANAGER_H__
#define __ESBSTAGEMANAGER_H__

#include "../ESBAManager.h"
#include "../presentation/ESBRenderer.h"
#include "ESBBox.h"

/**
 * Manages the actual "sound-box".
 */
class ESBStageManager: public ESBAManager
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:

        /**
         * Constructor.
         */
        ESBStageManager(ESBRenderer* apESBRenderer);


        /**
         * Destructor.
         */
        ~ESBStageManager(void);


        /**
         * Initialize.
         */
        void initialize(void);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
    private:


        ESBBox* mpESBBox;


        ESBRenderer* mpESBRenderer;
};

#endif