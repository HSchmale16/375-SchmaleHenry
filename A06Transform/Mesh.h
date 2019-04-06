#ifndef MESH_H_INC
#define MESH_H_INC

/**
 *
 * Mesh.h
 * A Mesh class for 3d graphics, point data is ordered as such
 * (x,y,z,r,g,b) for every vertex.
 *
 * Henry J Schmale
 * CSCI 375 Computer Graphics
 * Feb 10, 2019
 */

#include <vector>

#include <GL/glew.h>

#include "ShaderProgram.h"
#include "AiScene.h"

class Mesh {
public:
    Mesh();
    Mesh(const AiScene& s);
    Mesh(const Mesh&) = delete;
    Mesh& operator=(Mesh const&) = delete;

    ~Mesh();

    void
    addGeometry(const std::vector<float>& geometry);

    void
    prepareVao();

    void
    draw(ShaderProgram* shader, glm::mat4&);

    bool
    getUsesNormals() const;
private:
    GLuint m_vao;
    GLuint m_vbo;
    std::vector<float> m_geometry;
    bool usesNormals;
};

#endif // MESH_H_INC
