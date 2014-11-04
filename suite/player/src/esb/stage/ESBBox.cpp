#include "esb/stage/ESBBox.h"


const unsigned short ESBBox::INDICIES[] =  {0, 1,
                                            1, 2,
                                            2, 3,
                                            3, 0,
                                            4, 5,
                                            5, 6,
                                            6, 7,
                                            7, 4,
                                            0, 4,
                                            1, 5,
                                            2, 6,
                                            3, 7};


ESBBox::ESBBox(const unsigned int aDepth, 
               const unsigned int aHeight, 
               const unsigned int aWidth):
    mDepth(aDepth),
    mHeight(aHeight),
    mWidth(aWidth),
    mVisible(true),
    mVerticies()
{
    generateVerticies();
}


ESBBox::~ESBBox(void)
{
}


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
void ESBBox::generateVerticies()
{
    mVerticies[0].x = -0.5f * getWidth();
    mVerticies[0].y = 0.0f * getHeight();
    mVerticies[0].z = 0.0f * getDepth();
    mVerticies[1].x = 0.5f * getWidth();
    mVerticies[1].y = 0.0f * getHeight();
    mVerticies[1].z = 0.0f * getDepth();
    mVerticies[2].x = 0.5f * getWidth();
    mVerticies[2].y = 1.0f * getHeight();
    mVerticies[2].z = 0.0f * getDepth();
    mVerticies[3].x = -0.5f * getWidth();
    mVerticies[3].y = 1.0f * getHeight();
    mVerticies[3].z = 0.0f * getDepth();

    mVerticies[4].x = -0.5f * getWidth();
    mVerticies[4].y = 0.0f * getHeight();
    mVerticies[4].z = -1.0f * getDepth();
    mVerticies[5].x = 0.5f * getWidth();
    mVerticies[5].y = 0.0f * getHeight();
    mVerticies[5].z = -1.0f * getDepth();
    mVerticies[6].x = 0.5f * getWidth();
    mVerticies[6].y = 1.0f * getHeight();
    mVerticies[6].z = -1.0f * getDepth();
    mVerticies[7].x = -0.5f * getWidth();
    mVerticies[7].y = 1.0f * getHeight();
    mVerticies[7].z = -1.0f * getDepth();
}