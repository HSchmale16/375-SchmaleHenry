#include "Model.h"

Model::Model(const AiScene& s) {
    using namespace std::placeholders;
    m_current = m_meshes.insert(m_meshes.begin(), {"", nullptr});

    auto addChild = std::bind(&Model::addChildCallback,
            this, _1, _2, _3, _4);
    auto upCb = std::bind(&Model::ascendCallback, this);

    s.walkMeshes(upCb, addChild);
}

Model::Model(Mesh* mesh) {
    assert(mesh != nullptr);
    tree<std::pair<std::string,Mesh*>>::iterator top;
    m_meshes.append_child(top, {"", mesh});
}

Model::~Model() {

}

void
Model::draw(ShaderProgram* shader, const Transform& transform) {

}

void
Model::addChildCallback(
        const std::vector<float>& geo, 
        const std::vector<unsigned>& ind,
        const Transform& t,
        const std::string& name) {
    m_current = m_meshes.append_child(m_current,
            {name, new Mesh(ind, geo)});
}

void
Model::ascendCallback() {
    m_current = m_meshes.parent(m_current);
}
