#include "esb/stage/ESBBox.h"
#include "esb/stage/ESBStageManager.h"


ESBStageManager::ESBStageManager(ESBRenderer* apESBRenderer):
    mpESBBox(nullptr),
    mpESBRenderer(apESBRenderer)
{
}


ESBStageManager::~ESBStageManager(void)
{
    if(mpESBBox != nullptr)
    {
        delete mpESBBox;
        mpESBBox = nullptr;
    }
    mpESBRenderer = nullptr;
}


void ESBStageManager::initialize(void)
{
    mpESBBox = new ESBBox(800, 600, 800);
    mpESBRenderer->setBox(mpESBBox);
}