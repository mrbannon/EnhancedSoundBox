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
    // Create package manager.
    // ...

    // Let's try to load a package.
    // ...

    // Create the renderer.
    ESBRenderer* pESBRenderer = new ESBRenderer(1280, 960);
    pESBRenderer->initialize();

    // Great! We have a script and we know what we need to get. Everything is in place for this shitshow.
    // Let's hire/create a director. (The director will be given the package and take care of everything else).
    ESBDirector* pESBDirector = new ESBDirector(pESBRenderer);
    pESBDirector->initialize();

    // Go for it!
    pESBDirector->run();

    delete pESBDirector;
    delete pESBRenderer;

	SDL_Quit();
	return 0;
}