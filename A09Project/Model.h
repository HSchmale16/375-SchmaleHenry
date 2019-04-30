#ifndef MODEL_H_INC
#define MODEL_H_INC

#include "tree.hh"
#include "Mesh.h"
#include "AiScene.h"

using ModelTree = tree<std::pair<std::string,Mesh*>>;

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

    /**
     * Get a mesh by name, returns the occurance number found, in a 
     * pre order traversal.
     */
    Mesh*
    getMesh(std::string name, int occurance=0);

    void
    ascendCallback();

    Transform
    getWorld () const;
  
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
    void
    drawHelper(tree<std::pair<std::string,Mesh*>>::iterator it, Transform current);

    tree<std::pair<std::string,Mesh*>> m_meshes;
    tree<std::pair<std::string,Mesh*>>::iterator m_current;
    Transform m_world;

    void
    drawHelper(ModelTree::sibling_iterator iter, 
        ShaderProgram* shader,
        Transform t); 
};


#endif // MODEL_H_INC
