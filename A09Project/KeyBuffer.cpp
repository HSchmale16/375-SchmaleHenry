#include "KeyBuffer.h"

KeyBuffer::KeyBuffer() {}

void
KeyBuffer::setKeyDown(int key) {
    m_keys[key] = true;
}

void
KeyBuffer::setKeyUp(int key) {
    m_keys[key] = false;
}

void
KeyBuffer::reset() {
    m_keys.reset();
}

bool
KeyBuffer::isKeyDown(int key) const {
    return m_keys.test(key);
}
