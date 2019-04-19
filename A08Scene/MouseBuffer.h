#ifndef MOUSEBUFFER_H_INC
#define MOUSEBUFFER_H_INC

/** 
 * MouseBuffer.h
 * Henry J Schmale
 * A really stupid class to implement a mousebuffer
 * Spring 2019
 */

class MouseBuffer {
public:
    MouseBuffer();
    
    double
    getXPos() const;

    double
    getDx() const;

    double
    getDy() const;

    double
    getYPos() const;

    void
    setPosition(double x, double y); 

    void
    setButton(int button, int action, int mods);

    bool
    leftIsDown() const;

    bool
    rightIsDown() const;

private:
    bool m_leftDown;
    bool m_rightDown;
    double m_xpos;
    double m_oldx;
    double m_ypos;
    double m_oldy;
};

#endif // MOUSEBUFFER_H_INC
