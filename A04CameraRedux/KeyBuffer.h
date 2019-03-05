#ifndef KEYBUFFER_H_INC
#define KEYBUFFER_H_INC

#include <GLFW/glfw3.h>
#include <bitset>

/**
 * A basic keybuffer class that stores the state of the keyboard and
 * remembers it rather than having everyone access the keyboard.
 *
 * Henry J Schmale
 */

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
    isKeyDown(int key) const;
private:
    static const size_t NUM_KEYS = GLFW_KEY_LAST + 1;
    std::bitset<NUM_KEYS> m_keys;
};

#endif // KEYBUFFER_H_INC
