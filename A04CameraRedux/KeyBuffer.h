#ifndef KEYBUFFER_H_INC
#define KEYBUFFER_H_INC

#include <GLFW/glfw3.h>

class KeyBuffer {
public:
    KeyBuffer ();

    void
    setKeyDown(int key);

    void
    setKeyUp(int key);

    void
    reset();

    bool
    isKeyDown(int key const);
private:
    std::bitset<GLFW_KEY_LAST + 1> m_keys;
};

#endif // KEYBUFFER_H_INC
