#include "Scene.h"
#include <iostream>

using std::cout;
using std::endl;

/**
 * Scene.cpp
 *
 * Impl of Scene
 * Henry J Schmale
 * Spring 2019
 * CSCI 375
 */

Scene::Scene() {
    m_current = m_meshes.end();

    m_lights[0].position = Vector3(1000, 1000, 1000);
    m_lights[0].type = 1;
    m_lights[0].direction = Vector3(-1, -1, -1);
    m_lights[0].atten = Vector3(0.f);
    m_lights[0].diffuse = Vector3(0.5,1,1);
    m_lights[0].specular = Vector3(1,0.25,0.5);


    m_lights[1].position = Vector3(0,0,50);
    m_lights[1].type = 0;
    m_lights[1].direction = Vector3(0,0,1);
    m_lights[0].atten = Vector3(0.f);
    m_lights[1].diffuse = Vector3(0.5,0.75, 0.25);
    m_lights[1].specular = Vector3(0.5, 0, 0);

    m_max_active_light = 2;
}

Scene::~Scene() {
    clear();
}

void
Scene::add(const std::string& name, Model* mesh) {
    auto thing = m_meshes.find(name);

    if (thing != m_meshes.end()) {
        delete thing->second;
        thing->second = mesh;
    } else {
        m_meshes[name] = mesh;
    }

    if (m_current == m_meshes.end()) {
        setActiveMesh(name);
    }
}

void
Scene::remove(const std::string& name) {
    auto thing = m_meshes.find(name);
    if (thing != m_meshes.end()) {
        if (thing == m_current) {
            activateNextMesh();
        }
        m_meshes.erase(thing);
    }
}

void
Scene::clear() {
    for (auto& pm : m_meshes) {
        delete pm.second;
    }
    m_meshes.clear();
    m_current = m_meshes.end();
}

void
Scene::setActiveMesh(const std::string& name) {
    auto it = m_meshes.find(name);
    if (it != m_meshes.end()) {
        std::cout << "Active Mesh IS : " << it->first << " " << it->second << "\n";
        m_current = it;
    } else {
        std::cout << "Requested mesh is not found: " << name << std::endl;
    }
}

Model*
Scene::getActiveMesh() {
    return m_current->second;
}

Model*
Scene::getModel(std::string name) {
    auto thing = m_meshes.find(name);
    return thing != m_meshes.end() ? thing->second : nullptr;
}

const static char* formatStrings[] = {
    "uLights[%d].type",
    "uLights[%d].diffuseIntensity",
    "uLights[%d].specularIntensity",
    "uLights[%d].position",
    "uLights[%d].attenuationCoefficients",
    "uLights[%d].direction",
    "uLights[%d].cutoffCosAngle",
    "uLights[%d].falloff"
};

void
Scene::draw(ShaderProgram* s, Camera& c) {
    s->enable();

    s->setUniformMatrix("uView", c.getViewMatrix().getTransform());
    s->setUniformInt("uNumLights", m_max_active_light);
    for (size_t i = 0; i < m_max_active_light; ++i) {
        char buff[100];
        
        snprintf(buff, sizeof(buff), formatStrings[0], i);
        s->setUniformInt(buff, m_lights[i].type);

        snprintf(buff, sizeof(buff), formatStrings[1], i);
        s->setUniformVector(buff, m_lights[i].diffuse);
        
        snprintf(buff, sizeof(buff), formatStrings[2], i);
        s->setUniformVector(buff, m_lights[i].specular);
        
        snprintf(buff, sizeof(buff), formatStrings[3], i);
        s->setUniformVector(buff, m_lights[i].position);
        
        snprintf(buff, sizeof(buff), formatStrings[4], i);
        s->setUniformVector(buff, m_lights[i].atten);
        
        snprintf(buff, sizeof(buff), formatStrings[5], i);
        s->setUniformVector(buff, m_lights[i].direction);
    
        snprintf(buff, sizeof(buff), formatStrings[6], i);
        s->setUniformFloat(buff, m_lights[i].cutoff);
        
        snprintf(buff, sizeof(buff), formatStrings[7], i);
        s->setUniformFloat(buff, m_lights[i].falloff);
    
    }

    Transform t = c.getViewMatrix();
    for (const auto& m : m_meshes) {
        m.second->draw(s, t); 
    }
}

void
Scene::activateNextMesh() {
    ++m_current;
    if (m_current == m_meshes.end()) {
        m_current = m_meshes.begin();
    }
    cout << "PREV: MESH IS " << m_current->first << endl;
}

void
Scene::activatePreviousMesh() {
    --m_current;
    if (m_current == m_meshes.end()) { 
        --m_current;
    }
    cout << "NEXT: MESH IS " << m_current->first << endl;
}
