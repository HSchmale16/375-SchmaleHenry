/*
  Filename: AiScene.cpp
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg & Henry J Schmale
  Course: CSCI375
  Assignment: A06Transform
  Description: A class that simplifies importing scenes with the AssImp library.
*/

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <assimp/postprocess.h>

#include "AiScene.h"

AiScene::AiScene (const std::string& fileName)
{
  // Meshes may not consist of triangles, so have the importer
  //   triangulate.
  // Meshes may not have normals, so if they don't, have the importer
  //   generate them. 
  // Vertices may not be unique, so have them joined if they are the same.
  unsigned flags = aiProcess_Triangulate | 
        aiProcess_GenSmoothNormals |
        aiProcess_JoinIdenticalVertices;
  m_scene = m_importer.ReadFile (fileName, flags);
  if (m_scene == nullptr)
  {
    auto error = m_importer.GetErrorString ();
    fprintf (stderr, "Failed to load model %s with error '%s'. Exiting\n",
	     fileName.c_str (), error);
    exit (-1);
  }
}

static std::vector<float>
readVertexData(const aiMesh* mesh) {
  // Container for holding vertex data
  std::vector<float> vertexData;
  vertexData.reserve(mesh->mNumFaces * 6);

  for (unsigned vertexNum = 0; vertexNum < mesh->mNumVertices; ++vertexNum) {
    aiVector3D pos = mesh->mVertices[vertexNum];

    vertexData.push_back(pos.x);
    vertexData.push_back(pos.y);
    vertexData.push_back(pos.z);

    aiVector3D nor = mesh->mNormals[vertexNum];

    vertexData.push_back(nor.x);
    vertexData.push_back(nor.y);
    vertexData.push_back(nor.z);
  }

  return vertexData;
}

std::vector<float>
AiScene::readVertexData (unsigned meshNum) const
{
  assert(meshNum < m_scene->mNumMeshes);
  // Get the correct mesh object
  const aiMesh* mesh = m_scene->mMeshes[meshNum];
  return ::readVertexData(mesh);
}

static std::vector<unsigned>
readTriangleIndices(const aiMesh* mesh) {
  // Container for holding vertex data
  std::vector<unsigned> vertexData;
  vertexData.reserve(mesh->mNumFaces * 3);
  
  // Go through array of faces
  for (unsigned faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
  {
    // Get a face
    const aiFace& face = mesh->mFaces[faceNum];
    // Faces are triangles, so three indices
    const unsigned INDICES_PER_FACE = 3;
    // Go through the 3 indices
    for (unsigned indexNum = 0; indexNum < INDICES_PER_FACE; ++indexNum)
    {
      // Get vertex number at location "indexNum"
      // Indexing is used so data isn't duplicated

      auto vertexNum = face.mIndices[indexNum];

      vertexData.push_back(vertexNum);

    }
  }
  return vertexData;
}

std::vector<unsigned>
AiScene::readTriangleIndices(unsigned meshNum) const {
    assert(meshNum < m_scene->mNumMeshes);

  // Get the correct mesh object
  const aiMesh* mesh = m_scene->mMeshes[meshNum];
  return ::readTriangleIndices(mesh);
}

size_t
AiScene::countMeshes () const {
    return m_scene->mNumMeshes;
}

void
AiScene::walkMeshes(AscendCallback ascend, AddChildCallback child) const {
    walkHelper(m_scene->mRootNode, ascend, child);
}

void
AiScene::walkHelper(aiNode* node, 
        AscendCallback asc, AddChildCallback child) const {
    std::vector<unsigned> indexes;
    std::vector<float> geometry; 
    Transform t;
    std::string name = node->mName.C_Str();

    printf("%s\n", name.c_str());

    for(unsigned i = 0; i < node->mNumMeshes; ++i) {
        std::vector<float> got_geo = readVertexData(node->mMeshes[i]);
        std::vector<unsigned> got_ind = readTriangleIndices(node->mMeshes[i]);
        
        indexes.insert(indexes.end(), got_ind.begin(), got_ind.end());
        geometry.insert(geometry.end(), got_geo.begin(), got_geo.end());
    }

    aiMatrix4x4t m = node->mTransformation;
    Matrix3 orient (m.a1, m.b1, m.c1, m.a2, m.b2, m.c2, m.a3, m.b3, m.c3);
    Vector3 trans(m.a4, m.b4, m.c4);

    t.setOrientation(orient);
    t.setPosition(trans);
    
    // Now that we got the crap for the child let's walk through and do
    // the same for each child by recursing.
    if (geometry.size() > 0) 
        child(geometry, indexes,t, name); 
    for (unsigned i = 0; i < node->mNumChildren; ++i) {
        walkHelper(node->mChildren[i], asc, child);
    }
    if (geometry.size() > 0) 
        asc();
}
