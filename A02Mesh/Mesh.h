#ifndef MESH_H_INC
#define MESH_H_INC

#include <vector>

#include <GL/glew.h>

class Mesh {
public:
    Mesh();
    ~Mesh();

    void
    addGeometry(const std::vector<float>& geometry);

    void
    prepareVao();

    void
    draw();

private:
    GLuint m_vao;
    GLuint m_vbo;
    std::vector<float> m_geometry;
};

#endif // MESH_H_INC
