#include "esb/ESBDirector.h"
#include "lazyfoo/LTimer.h"


const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
ESBDirector::ESBDirector(ESBRenderer* apESBRenderer, ESBActorManager* apESBActorManager):
    mpESBActorManager(apESBActorManager),
    mpESBRenderer(apESBRenderer),
    mpESBStageManager(nullptr)
{
}


ESBDirector::~ESBDirector(void)
{
    if (mpESBStageManager != nullptr)
    {
        delete mpESBStageManager;
        mpESBStageManager = nullptr;
    }
}


void ESBDirector::initialize(void)
{
    // Create and initialize managers and other stuff.
    mpESBStageManager = new ESBStageManager(mpESBRenderer);
    mpESBStageManager->initialize();
}


void ESBDirector::run(void)
{
    bool quit = false;
    SDL_Event event;

    LTimer fpsTimer;
    LTimer capTimer;

    //Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();

    // The loop!
    printMessage("Starting run loop...");
    while(!quit)
    {
        // Start cap timer.
        capTimer.start();

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Update, render.
        unsigned int fpsTicks = fpsTimer.getTicks();
        mpESBActorManager->update(fpsTicks);
        mpESBRenderer->render();

        // Phew.  Now some helpful info.
        float avgFPS = countedFrames / ( fpsTicks / 1000.f );
        if(avgFPS > 2000000)
        {
            avgFPS = 0;
        }
        //printMessage("FPS: " + std::to_string(avgFPS) + ", current tick index: " + std::to_string(fpsTicks));

        // Check frame rate.
        ++countedFrames;
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
void ESBDirector::setCameraAtListenPoint()
{
  //  mpESBCamera->moveLoc(0.0f, 0.0f, 0.0f);
}


void ESBDirector::setCameraOutside()
{
  //  mpESBCamera->moveLoc(0.0f, 400.0f, 1000.0f);
}

