#ifndef MOUSEBUFFER_H_INC
#define MOUSEBUFFER_H_INC

#include <GLFW/glfw3.h>

class MouseBuffer {
public:
    MouseBuffer();

private:
    bool m_leftDown;
    bool m_rightDown;
    

};

#endif // MOUSEBUFFER_H_INC
