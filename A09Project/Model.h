#ifndef MODEL_H_INC
#define MODEL_H_INC

#include "tree.hh"
#include "Mesh.h"
#include "AiScene.h"

class Model {
public:
    Model(const AiScene& s);

private:

    tree<Mesh*> m_meshes;
};


#endif // MODEL_H_INC
