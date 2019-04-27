/**
 * Mesh.cpp
 * Henry J Schmale
 * CSCI 375 - Spring 2019
 *
 */

#include "Mesh.h"
#include <cassert>
#include <iostream>


Mesh::Mesh () 
: usesNormals(false) {
    glGenVertexArrays (1, &m_vao);
    glGenBuffers (1, &m_vbo);
    glGenBuffers(1, &m_ibo);
}

Mesh::Mesh (const AiScene& scene) 
: usesNormals(true) {
    glGenVertexArrays (1, &m_vao);
    glGenBuffers(1, &m_vbo); 
    glGenBuffers(1, &m_ibo);

    for (size_t i = 0; i < scene.countMeshes(); ++i) {
        std::vector<unsigned> ids = scene.readTriangleIndices(i);
        std::vector<float> geo = scene.readVertexData(i);

        unsigned offset = m_geometry.size() / 6;
        for (auto& id : ids) {
            id += offset;
        }
        m_indices.insert(m_indices.end(), ids.begin(), ids.end());
        m_geometry.insert(m_geometry.end(), geo.begin(), geo.end());

    }
    prepareVao();
}

Mesh::Mesh(const AiScene& scene, int MeshNum) 
: usesNormals(true) {
    glGenVertexArrays (1, &m_vao);
    glGenBuffers(1, &m_vbo); 
    glGenBuffers(1, &m_ibo);
    
    std::vector<unsigned> ids = scene.readTriangleIndices(MeshNum);
    std::vector<float> geo = scene.readVertexData(MeshNum);
    m_indices.insert(m_indices.end(), ids.begin(), ids.end());
    m_geometry.insert(m_geometry.end(), geo.begin(), geo.end());
    prepareVao();
}

Mesh::Mesh(const std::vector<unsigned>& ind, const std::vector<float>& geo) 
: m_indices(ind), m_geometry(geo), usesNormals(true){
    glGenVertexArrays (1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    prepareVao();
}

Mesh::~Mesh () {
    glDeleteVertexArrays (1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
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


    // upload indexing data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        m_indices.size() * sizeof(unsigned),
        m_indices.data(),
        GL_STATIC_DRAW);


    glBindVertexArray (0);
}

void 
Mesh::draw(ShaderProgram* shader, const Transform& view) {

    shader->enable(); 

    Transform t(view);
    t.combine(m_world);

    shader->setUniformMatrix("uModelView", t.getTransform());

    glBindVertexArray(m_vao);
    //glDrawArrays(GL_TRIANGLES, 0, m_geometry.size() / 6);
    glDrawElements (GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 
        reinterpret_cast<void*>(0));
    glBindVertexArray(0);

    shader->disable();
}

bool
Mesh::getUsesNormals() const {
    return usesNormals;
}

Transform
Mesh::getWorld () const {
    return m_world;
}

void 
Mesh::moveRight(float d) {
    m_world.moveRight(d);
}

void
Mesh::moveUp(float d) {
    m_world.moveUp(d);
}

void
Mesh::moveBack(float d) {
    m_world.moveBack(d);
}

void
Mesh::moveLocal(float d, const Vector3& loc) {
    m_world.moveLocal(d, loc);
}

void
Mesh::moveWorld (float d, const Vector3& wd) {
    m_world.moveWorld(d, wd);
}

void
Mesh::pitch(float angleDegrees) {
    m_world.pitch(angleDegrees);
}

void
Mesh::yaw(float angDegrees) {
    m_world.yaw(angDegrees);
}

void
Mesh::roll(float angDegrees) {
    m_world.roll(angDegrees);
}

void
Mesh::rotateLocal(float angleDegrees, const Vector3& axis) {
    m_world.rotateLocal(angleDegrees, axis);
}

void
Mesh::alignWithWorldY () {
    m_world.alignWithWorldY();
}

void
Mesh::scaleLocal (float s) {
    m_world.scaleLocal(s);
}

void
Mesh::scaleLocal(float x, float y, float z) {
    m_world.scaleLocal(x, y, z);
}

void
Mesh::scaleWorld(float s) {
    m_world.scaleWorld(s);
}

void
Mesh::scaleWorld(float x, float y, float z) {
    m_world.scaleWorld(x, y, z);
}

void
Mesh::shearLocalXByYz(float y, float z) {
    m_world.shearLocalXByYz(y, z);
}

void
Mesh::shearLocalYByXz(float x, float z) {
    m_world.shearLocalYByXz(x, z);
}

void
Mesh::shearLocalZByXy(float x, float y) {
    m_world.shearLocalZByXy(x, y);
}

