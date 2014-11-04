/**
 * Note: a lot of this from http://lazyfoo.net/tutorials/SDL/50_SDL_and_opengl_2/index.php.
 */
#include <cmath>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "esb/presentation/ESBRenderer.h"


///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
ESBRenderer::ESBRenderer(unsigned int aWindowWidth,
                         unsigned int aWindowHeight):
mpESBCamera(nullptr),
mpActorVector(nullptr),
mpESBBox(nullptr),
mSDLGLContext(),
mpSDLRenderer(nullptr),
mpSDLWindow(nullptr),
mWindowHeight(aWindowHeight),
mWindowWidth(aWindowWidth)
{
    test = 0;
}


ESBRenderer::~ESBRenderer()
{
    mpESBBox = nullptr;
    setActorVector(nullptr);
    SDL_DestroyRenderer(mpSDLRenderer);
    SDL_DestroyWindow(mpSDLWindow);
}


void ESBRenderer::initialize()
{
    initializeSDL();
    initializeGL();
}


void ESBRenderer::setCamera(ESBCamera* apESBCamera)
{
    mpESBCamera = apESBCamera;
}


void ESBRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    mpESBCamera->setView();
    draw();
    //SDL_RenderCopy(ren, tex, NULL, NULL);
    //SDL_RenderPresent(mpSDLRenderer);


    // Camera???
 /*   glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  //  gluPerspective(45, mWindowWidth / (double)mWindowHeight, 0.1, 4333.0);
    test += 1;
    glTranslatef(0, 0, test);*/

    SDL_GL_SwapWindow(mpSDLWindow);
}


void ESBRenderer::setBox(ESBBox* apESBBox)
{
    mpESBBox = apESBBox;
}
        

void ESBRenderer::setActorVector(std::vector<ESBActor*>* apActorVector)
{
    mpActorVector = apActorVector;
}


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
void ESBRenderer::draw()
{
    drawBox();
    drawActors();
}


void ESBRenderer::drawActor(ESBActor* apESBActor)
{
    glMatrixMode(GL_MODELVIEW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
    glVertexPointer(3, GL_FLOAT, sizeof(vertex), apESBActor->getVerticies());

    // Our temporary translation matrix. (May change in future).
    float xTranslate = apESBActor->getPan() * (mpESBBox->getWidth() / 2);
    float yTranslate = apESBActor->getRegister() * mpESBBox->getHeight();

    // Presence is a little harder...
    float depth = (apESBActor->getPresence() - 1.0f) * (mpESBBox->getDepth() * 2);
    float zTranslate = depth;
    /*float zTranslate = -1 * sqrt(pow(depth, 2) - pow(xTranslate, 2));*/
    mpESBCamera->setView();
    glTranslatef(xTranslate, yTranslate, zTranslate);
    glColor3f(1.0f,0.0f,0.0f); 

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, apESBActor->getIndicies());
    glDisableClientState(GL_VERTEX_ARRAY);
}


void ESBRenderer::drawActors()
{
    for(std::vector<ESBActor*>::const_iterator iterator = mpActorVector->begin(); iterator != mpActorVector->end(); ++iterator) 
    {
        ESBActor* pESBActor = *iterator;
        if(pESBActor->isVisible())
        {
            drawActor(pESBActor);
        }
    }
}


void ESBRenderer::drawBox()
{
    glMatrixMode(GL_MODELVIEW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glLoadIdentity();
    glVertexPointer(3, GL_FLOAT, sizeof(vertex), mpESBBox->getVerticies());
    mpESBCamera->setView();
    glColor3f(1.0f,1.0f,1.0f); 
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, mpESBBox->getIndicies());
    glDisableClientState(GL_VERTEX_ARRAY);
}


void ESBRenderer::initializeGL()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45, mWindowWidth / (double)mWindowHeight, 0.1, 4333.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}


void ESBRenderer::initializeSDL()
{
    // TODO this is lazy...do error checking
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    mpSDLWindow = SDL_CreateWindow("GIVE ME A NAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    mpSDLRenderer = SDL_CreateRenderer(mpSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    mSDLGLContext = SDL_GL_CreateContext(mpSDLWindow);
    SDL_GL_SetSwapInterval(1);
}
