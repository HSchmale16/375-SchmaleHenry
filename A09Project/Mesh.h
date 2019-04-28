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
#include "Transform.h"

class Mesh {
public:
    Mesh();
    Mesh(const AiScene& s);
    Mesh(const AiScene& s, int meshNum);
    Mesh(const std::vector<unsigned>& ind, const std::vector<float>& geo);

    // Remove access
    Mesh(const Mesh&) = delete;
    Mesh& operator=(Mesh const&) = delete;

    ~Mesh();

    void
    addGeometry(const std::vector<float>& geometry);

    void
    prepareVao();

    void
    draw(ShaderProgram* shader, const Transform&);

    bool
    getUsesNormals() const;
  
    Transform
    getWorld () const;

    void
    setWorld(const Transform& t);
  
    // Key: "1"
    void
    moveRight (float distance);
  
    // Key: "2"
    void
    moveUp (float distance);
  
    void
    moveBack (float distance);
  
    void
    moveLocal (float distance, const Vector3& localDirection);
  
    // Key: "3"
    void
    moveWorld (float distance, const Vector3& worldDirection);
  
    // Key: "4"
    void
    pitch (float angleDegrees);
  
    // Key: "5"
    void
    yaw (float angleDegrees);
  
    // Key: "6"
    void
    roll (float angleDegrees);
  
    void
    rotateLocal (float angleDegrees, const Vector3& axis);
  
    // Key: "7"
    void
    alignWithWorldY ();
  
    // Key: "8"
    void
    scaleLocal (float scale);
  
    void
    scaleLocal (float scaleX, float scaleY, float scaleZ);
      
    // Key: "9"
    void
    scaleWorld (float scale);
  
    void
    scaleWorld (float scaleX, float scaleY, float scaleZ);
  
    // Key: "0"
    void
    shearLocalXByYz (float shearY, float shearZ);
  
    void
    shearLocalYByXz (float shearX, float shearZ);
  
    void
    shearLocalZByXy (float shearX, float shearY);
private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;
    Transform m_world;

    std::vector<unsigned> m_indices;
    std::vector<float> m_geometry;

    bool usesNormals;
};

#endif // MESH_H_INC
