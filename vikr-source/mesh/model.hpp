//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MODEL_HPP
#define __VIKR_MODEL_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>

// Going to need group command on this one...

// Assimp importers.
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Materials and mesh.
#include <mesh/mesh.hpp>
#include <shader/material.hpp>
#include <shader/texture.hpp>

// std headers.
#include <string>

namespace vikr {


class GroupCommand;
/**
  Model is a class intended for importing various different 
  graphical models that are imported from graphics software like
  Maya, 3DSMax, and Blender. 
*/
class Model {
public:
  Model(std::string path);

  

protected:
  vvoid LoadModel(std::string path);
  vvoid ProcessNode(aiNode *node, const aiScene *scene);
  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string type_name);

private:

  

  std::vector<Mesh> m_meshes;
  std::vector<Texture> m_textures;

};
} // vikr
#endif // __VIKR_MODEL_HPP