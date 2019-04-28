#include "Model.h"
#include <iostream>

using std::begin;
using std::end;
using std::cout;
using std::endl;

Model::Model(const AiScene& s) {
    using namespace std::placeholders;
    m_current = m_meshes.insert(m_meshes.begin(), {"", nullptr});

    auto addChild = std::bind(&Model::addChildCallback,
            this, _1, _2, _3, _4);
    auto upCb = std::bind(&Model::ascendCallback, this);

    s.walkMeshes(upCb, addChild);
    
    m_current = m_meshes.begin();

    std::cout << m_meshes.size() << std::endl;
    std::cout << std::distance(begin(m_meshes), end(m_meshes)) << std::endl;
}

Model::Model(Mesh* mesh) {
    assert(mesh != nullptr); 
    m_current = m_meshes.insert(m_meshes.begin(), {"", mesh});
}

Model::~Model() {
    for(auto it = begin(m_meshes); it != end(m_meshes); ++it) {
        if(it->second != nullptr)
            delete it->second;
    }
}

void
Model::draw(ShaderProgram* shader, const Transform& view) {

    Transform t(view);
    t.combine(m_world);

    for(auto it = begin(m_meshes); it != end(m_meshes); ++it) {
        if (it->second != nullptr) {
            it->second->draw(shader, t);
        }
    }
}

void
Model::addChildCallback(
        const std::vector<float>& geo, 
        const std::vector<unsigned>& ind,
        const Transform& t,
        const std::string& name) {

    std::cout << t << std::endl;
    m_current = m_meshes.append_child(m_current,
            {name, new Mesh(ind, geo)});

    m_current->second->setWorld(t);
}

void
Model::ascendCallback() {
    m_current = m_meshes.parent(m_current);
}


Transform
Model::getWorld () const {
    return m_world;
}

void 
Model::moveRight(float d) {
    m_world.moveRight(d);
}

void
Model::moveUp(float d) {
    m_world.moveUp(d);
}

void
Model::moveBack(float d) {
    m_world.moveBack(d);
}

void
Model::moveLocal(float d, const Vector3& loc) {
    m_world.moveLocal(d, loc);
}

void
Model::moveWorld (float d, const Vector3& wd) {
    m_world.moveWorld(d, wd);
}

void
Model::pitch(float angleDegrees) {
    m_world.pitch(angleDegrees);
}

void
Model::yaw(float angDegrees) {
    m_world.yaw(angDegrees);
}

void
Model::roll(float angDegrees) {
    m_world.roll(angDegrees);
}

void
Model::rotateLocal(float angleDegrees, const Vector3& axis) {
    m_world.rotateLocal(angleDegrees, axis);
}

void
Model::alignWithWorldY () {
    m_world.alignWithWorldY();
}

void
Model::scaleLocal (float s) {
    m_world.scaleLocal(s);
}

void
Model::scaleLocal(float x, float y, float z) {
    m_world.scaleLocal(x, y, z);
}

void
Model::scaleWorld(float s) {
    m_world.scaleWorld(s);
}

void
Model::scaleWorld(float x, float y, float z) {
    m_world.scaleWorld(x, y, z);
}

void
Model::shearLocalXByYz(float y, float z) {
    m_world.shearLocalXByYz(y, z);
}

void
Model::shearLocalYByXz(float x, float z) {
    m_world.shearLocalYByXz(x, z);
}

void
Model::shearLocalZByXy(float x, float y) {
    m_world.shearLocalZByXy(x, y);
}

