/**
 * Note: a lot of this from http://lazyfoo.net/tutorials/SDL/50_SDL_and_opengl_2/index.php.
 */
#include <cmath>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "esb/presentation/ESBRenderer.h"


 #define PI 3.14159265
 #define PI_HALF 1.57079632
 #define RADIAN_TO_ANGLE 180 / PI


///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
ESBRenderer::ESBRenderer(unsigned int aWindowWidth,
                         unsigned int aWindowHeight):
mpActorVector(nullptr),
mpESBBox(nullptr),
mSDLGLContext(),
mpSDLRenderer(nullptr),
mpSDLWindow(nullptr),
mWindowHeight(aWindowHeight),
mWindowWidth(aWindowWidth)
{
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


void ESBRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    draw();
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


/* taken from http://stackoverflow.com/questions/22886364/load-texture-using-opengl-and-c */
unsigned int ESBRenderer::loadBMP(const char *fileName)
{
    FILE *file;
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int size;
    unsigned int width, height;
    unsigned char *data;


    file = fopen(fileName, "rb");

    if (file == NULL)
    {
        printErrorMessage("invaild texture file path");
        printErrorMessage(fileName);
        return false;
    }

    if (fread(header, 1, 54, file) != 54)
    {
        printErrorMessage("invaild texture file; header not right size");
        printErrorMessage(fileName);
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        printErrorMessage("invaild texture file; initial header characters incorrect");
        printErrorMessage(fileName);
        return false;
    }

    dataPos     = *(int*)&(header[0x0A]);
    size        = *(int*)&(header[0x22]);
    width       = *(int*)&(header[0x12]);
    height      = *(int*)&(header[0x16]);

    if (size == NULL)
        size = width * height * 3;
    if (dataPos == NULL)
        dataPos = 54;

    data = new unsigned char[size];

    fread(data, 1, size, file);

    fclose(file);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    std::string fileNameString(fileName);
    printMessage("loaded '" + fileNameString + "', ID " + std::to_string(texture));

    return texture;
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
    // Set mode.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set camera.
    gluLookAt(0, 300, 1000, 0, 300, 0, 0, 1, 0);

    // Set up translation. Our temporary translation matrix. (May change in future).
    float xTranslate = apESBActor->getPan() * (mpESBBox->getWidth() / 2);
    float yTranslate = apESBActor->getRegister() * mpESBBox->getHeight();
    float depth = (apESBActor->getPresence() - 1.0f) * (mpESBBox->getDepth() * 2);
    float zTranslate = depth;
    glTranslatef(xTranslate, yTranslate, zTranslate);

    // Enable some junk
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // ???
    glBindTexture(GL_TEXTURE_2D, apESBActor->getTextureId());

    // Enable states.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Set array pointers.
    glVertexPointer(3, GL_FLOAT, sizeof(vertex), apESBActor->getVerticies());
    glTexCoordPointer(2, GL_FLOAT, 0, apESBActor->getTextureCoordinates());

    // Define alpha.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, apESBActor->getPresence()); 

    // Draw.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, apESBActor->getIndicies());

    // Disable and go home.
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
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
    // Set mode.
    glMatrixMode(GL_MODELVIEW);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Load identity.
    glLoadIdentity();

    // Set vertex array pointer.
    glVertexPointer(3, GL_FLOAT, sizeof(vertex), mpESBBox->getVerticies());

    // Camera (fix).
    gluLookAt(0, 300, 1000, 0, 300, 0, 0, 1, 0);

    // Color.
    glColor3f(1.0f,1.0f,1.0f); 

    // Draw and go home.
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, mpESBBox->getIndicies());
    glDisableClientState(GL_VERTEX_ARRAY);
}


void ESBRenderer::initializeGL()
{
    // TEST



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
