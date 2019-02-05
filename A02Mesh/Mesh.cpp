#include "Mesh.h"
#include <cassert>

Mesh::Mesh () {
    glGenVertexArrays (1, &m_vao);
    glGenBuffers (1, &m_vbo);
}

Mesh::~Mesh () {
    glDeleteVertexArrays (1, &m_vao);
}

void
Mesh::addGeometry (const std::vector<float>& geometry) {
    assert (geometry.size() % 6 == 0);
    m_geometry.insert (m_geometry.end(), geometry.begin(), geometry.end());
    this->prepareVao();
}

void
Mesh::prepareVao () {
    glBindVertexArray (m_vao);
    glBindBuffer (GL_ARRAY_BUFFER, m_vbo);
    
    glBufferData (GL_ARRAY_BUFFER, m_geometry.size () * sizeof (float),
        m_geometry.data (),
        GL_STATIC_DRAW);
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
        reinterpret_cast<void*> (0));
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
        reinterpret_cast<void*> (3 * sizeof (float)));
    glBindVertexArray (0);
}

void 
Mesh::draw() {
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_geometry.size() / 6);
    glBindVertexArray(0);
}

