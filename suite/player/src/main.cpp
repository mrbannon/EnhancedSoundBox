#include <iostream>
#include <string>
#include <SDL.h>
#include "esb/ESB.h"
#include "ResourcePath.h"

/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
int main(int argc, char** argv)
{
    // Create the renderer.
    ESBRenderer* pESBRenderer = new ESBRenderer(1280, 960);
    pESBRenderer->initialize();

    // Create our actor manager.
    ESBActorManager* pESBActorManager = new ESBActorManager(pESBRenderer);
    pESBActorManager->initialize();

    // Let's try to load a package. This will create the actors, load the textures, yada yada.
    ESBPackage* pESBPackage = new ESBPackage(argv[1], pESBActorManager, pESBRenderer);

    // Great! We have a script and we know what we need to get. Everything is in place for this shitshow.
    // Let's hire/create a director. It will run everything.
    ESBDirector* pESBDirector = new ESBDirector(pESBRenderer, pESBActorManager);
    pESBDirector->initialize();

    // Go for it!
    pESBDirector->run();

    delete pESBDirector;
    delete pESBPackage;
    delete pESBActorManager;
    delete pESBRenderer;

	SDL_Quit();
	return 0;
}