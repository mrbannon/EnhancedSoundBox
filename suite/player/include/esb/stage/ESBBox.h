#ifndef __ESBBOX_H__
#define __ESBBOX_H__


#include "../ESBABase.h"


/**
 * The "box".
 */
class ESBBox: public ESBABase
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
    public:

        /**
         * Constructor.
         */
        ESBBox(const unsigned int aDepth, 
               const unsigned int aHeight, 
               const unsigned int aWidth);


        /**
         * Destructor.
         */
        ~ESBBox(void);


        inline bool isVisible() { return mVisible; };
        inline unsigned int getDepth() { return mDepth; };
        inline unsigned int getHeight() { return mHeight; };
        inline unsigned int getWidth() { return mWidth; };
        inline vertex* getVerticies() { return mVerticies; }
        inline const unsigned short* getIndicies() const { return INDICIES; }


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
    private:


        void generateVerticies();


        static const unsigned short INDICIES[];
        unsigned int mDepth;
        unsigned int mHeight;
        unsigned int mWidth;
        bool mVisible;
        vertex mVerticies[8];
};

#endif