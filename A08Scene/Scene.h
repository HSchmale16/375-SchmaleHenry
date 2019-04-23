/*
  File: Scene.h
  Author: Chad Hogg & Henry J Schmale
  Course: CSCI375
  Assignment: A08Scene
  Description: A collection of all Meshes in the world.
*/

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <map>

#include "Mesh.h"
#include "Camera.h"

class Scene
{
 public:
  // Initialize this Scene.
  // You may want to have multiple ctors.
  // Determine sensible parameters. 
  Scene ();

  // Remove all meshes from this Scene.
  // Resource management is up to you (whether you release
  //   mesh resources (VAOs, VBOs, IBOs, etc.).
  ~Scene ();

  // Prevent Scene-s from being copied and copy assigned!
  Scene(const Scene&) = delete;
  
  Scene&
  operator=(const Scene&) = delete;

  // Add Mesh "mesh" with name "meshName" to this Scene. 
  // Return type is up to you
  void
  add (const std::string& meshName, Mesh* mesh);

  // Remove the mesh named "meshName" from this Scene. 
  // Return type is up to you.
  // Whether you destroy the mesh is up to you.
  void
  remove (const std::string& meshName);

  // Remove all meshes from this Scene.
  // Whether you destroy them is up to you.
  void
  clear ();

  // Set the active mesh to the mesh named "meshName".
  // The active mesh is the one affected by transforms. 
  void
  setActiveMesh (const std::string& meshName);

  // Return the active mesh. 
  Mesh*
  getActiveMesh ();

  // Draw all meshes in this Scene.
  // Determine sensible parameters. 
  void
  draw (ShaderProgram* s, Camera& c);

  // Changes the active mesh to the next one.
  // Switch to first if you were at last.
  void
  activateNextMesh ();

  // Changes the active mesh to the previous one.
  // Switch to last if you were at first.
  void
  activatePreviousMesh ();


 private:
  //TODO: Some data members will be needed
  std::map<std::string,Mesh*> m_meshes;
  std::map<std::string,Mesh*>::iterator m_current;
};

#endif//SCENE_H
