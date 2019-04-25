#include "MouseBuffer.h"
#include <GLFW/glfw3.h>

/**
 * Impl of MouseBuffer.h
 *
 * Henry J Schmale
 * Spring 2019
 *
 */

MouseBuffer::MouseBuffer() {}

double
MouseBuffer::getXPos() const {
    return m_xpos;
}

double
MouseBuffer::getYPos() const {
    return m_ypos;
}

void
MouseBuffer::setPosition(double x, double y) {
    m_oldx = m_xpos;
    m_xpos = x;
    m_oldy = m_ypos;
    m_ypos = y;
}

void
MouseBuffer::setButton(int button, int action, int mods) {
    if (action == GLFW_RELEASE) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            m_leftDown = false;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            m_rightDown = false;
        } 
    }

    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            m_leftDown = true;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            m_rightDown = true;
        }
    }
}

double
MouseBuffer::getDx() const {
    return m_oldx - m_xpos; 
}

double
MouseBuffer::getDy() const {
    return m_oldy - m_ypos;
}

bool
MouseBuffer::leftIsDown() const {
    return m_leftDown;
}

bool
MouseBuffer::rightIsDown() const {
    return m_rightDown;
}
