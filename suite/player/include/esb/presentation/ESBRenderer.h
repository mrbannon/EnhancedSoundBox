#ifndef __ESBRENDERER_H__
#define __ESBRENDERER_H__


#include <map>
#include <SDL.h>
#include <vector>
#include "../ESBABase.h"
#include "../actor/ESBActor.h"
#include "../presentation/ESBRenderer.h"
#include "../stage/ESBBox.h"


/**
 * ESB renderer
 */
class ESBRenderer: public ESBABase
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:


        /**
         * Constructor.
         */
        ESBRenderer(unsigned int aWindowWidth,
                    unsigned int aWindowHeight);


        /**
         * Destructor.
         */
        ~ESBRenderer();


        /**
         * Temporary.
         */
        void initialize();


        /**
         * Render.
         */
        void render();


        /**
         * Sets a box to the scene.
         */
        void setBox(ESBBox* apESBBox);


        /**
         * Adds actors to the scene.
         */
        void setActorVector(std::vector<ESBActor*>* avActorVector);


        /**
         * Loads texture.
         */
        void loadTexture(std::string aTextureName, std::string aTextureFilePath);


        /**
         * Gets texture ID by name.
         */
        unsigned int getTextureIdByName(std::string aTextureName);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
    private:


        /**
         * Draws all objects.
         */
        void draw();


        /**
         * Draw actor.
         */
        void drawActor(ESBActor* apESBActor);


        /**
         * Draw actors.
         */
        void drawActors();


        /**
         * Draws box.
         */
        void drawBox();


        /**
         * Draws boxes.
         */
        void drawBoxes();


        /**
         * Initialize GL.
         */
        void initializeGL();


        /**
         * Initialize SDL.
         */
        void initializeSDL();


        /**
         * Loads BMP to texture data and returns texture ID.
         */
        unsigned int loadBMP(const char *fileName);


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
    private:


        std::vector<ESBActor*>* mpActorVector;
        ESBBox* mpESBBox;
        SDL_GLContext mSDLGLContext;
        SDL_Renderer* mpSDLRenderer;
        SDL_Window* mpSDLWindow;
        unsigned int mWindowHeight;
        unsigned int mWindowWidth;
        std::map<std::string, unsigned int> mTextureMap;
};

#endif