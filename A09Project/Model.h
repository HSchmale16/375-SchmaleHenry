#ifndef MODEL_H_INC
#define MODEL_H_INC

#include "tree.hh"
#include "Mesh.h"
#include "AiScene.h"

class Model {
public:
    Model(const AiScene& s);
    Model(Mesh* mesh);
    ~Model();

    void
    draw(ShaderProgram* shader, const Transform& transform);

    void
    addChildCallback(
        const std::vector<float>& geo,
        const std::vector<unsigned>& ind,
        const Transform& t,
        const std::string& name);

    void
    ascendCallback();

private:
    void
    drawHelper(tree<std::pair<std::string,Mesh*>>::iterator it, Transform current);

    tree<std::pair<std::string,Mesh*>> m_meshes;
    tree<std::pair<std::string,Mesh*>>::iterator m_current;
};


#endif // MODEL_H_INC
