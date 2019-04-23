#include "Scene.h"
#include <iostream>
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
}

Scene::~Scene() {
    clear();
}

void
Scene::add(const std::string& name, Mesh* mesh) {
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
    m_current = m_meshes.find(name);
}

Mesh*
Scene::getActiveMesh() {
    return m_current->second;
}

void
Scene::draw(ShaderProgram* s, Camera& c) {
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
}

void
Scene::activatePreviousMesh() {
    --m_current;
    if (m_current == m_meshes.end()) { 
        --m_current;
    }
}
