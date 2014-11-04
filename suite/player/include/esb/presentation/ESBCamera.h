#ifndef __ESBCAMERA_H__
#define __ESBCAMERA_H__


#include <SDL_opengl.h>


/*
http://www.flipcode.com/archives/OpenGL_Camera.shtml

Usage:
You can access the Right/Up/Forward vectors like a float[3] array,
but cannot write to them, because that would screw up the matrix.
Same goes for Position, except its safe to write to it.

setView() has to be called before you draw anything.
Just call it instead of gluLookAt (which most are using)

move and rotate come in two versions. Loc means the transformation
is in local coords, so rotating around (1,0,0) means youre rotating
around your current Right-vector while Glob would rotate around the
global x-axis.

Most likely you will use Loc for controlling the camera, though Glob
can be usefull if you need to apply physics. Also walking characters
will usually rotate around the global rather than around their local Up,
while flying objects will always use local axes.

If talking about objects when this is a camera confuses you: if you drop
the setView() method you can use this for objects in your world too. Just
rename the class to Object3D or something and derive a camera class from it.
*/
class ESBCamera {
public:
    float const *Right, *Up, *Forward;
    float *Position;
private:
    float Transform[16];

public:
    ESBCamera(float x=0.0f, float y=0.0f, float z=0.0f);
    ~ESBCamera();

    void setView();
    void moveLoc(float x, float y, float z, float distance=1);
    void moveGlob(float x, float y, float z, float distance=1);
    void rotateLoc(float deg, float x, float y, float z);
    void rotateGlob(float deg, float x, float y, float z);
};

#endif